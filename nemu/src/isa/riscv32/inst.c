/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write
#define signed_min -2147483648
enum {
  TYPE_I, TYPE_U, TYPE_S, TYPE_J, TYPE_R, TYPE_B,

  TYPE_N, // none，无立即数类型
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS( i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12),20) << 12; } while(0)

#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = SEXT((BITS(i, 31, 31) << 20 | BITS(i, 30, 21) <<1 | BITS(i, 20, 20) << 11 | BITS(i, 19, 12) << 12), 20); } while (0)
#define immB() do { *imm = SEXT((BITS(i, 31, 31) << 12 | BITS(i, 30, 25) <<5 | BITS(i, 11,8) <<1 | BITS(i,7,7) <<11), 13); } while (0)



static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J: src1R();          immJ(); break;
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_B: src1R(); src2R(); immB(); break;
    case TYPE_N: break;
    default: panic("unsupported type = %d", type);
  }
}

// LR/SC reservation for RV32A (single-core approximation)
static bool lr_valid = false;
static vaddr_t lr_addr = 0;

static int decode_exec(Decode *s) {
  s->dnpc = s->snpc;

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}

  // Check for compressed instructions (16-bit)
  // The last 2 bits are not 11 (binary) or 3 (decimal)
  if ((s->isa.inst & 0x3) != 3) {
      // Correct PC for compressed instructions: they are 2 bytes long, not 4.
      // inst_fetch advanced snpc by 4, so we need to fix dnpc.
      s->dnpc = s->pc + 2;
      
      uint32_t i = s->isa.inst;
      int rd = 0;
      word_t src1 = 0, src2 = 0, imm = 0;
      // Simple macro to help with decoding compressed instructions
      // This is a simplified approach. A full implementation would need more robust decoding.
      // We map compressed instructions to their 32-bit equivalents logic directly.

      // C.ADDI4SPN (000): addi rd', x2, nzuimm
      if ((i & 0xe003) == 0x0000) { // 000 ... ... ... 00
          int rd_prime = BITS(i, 4, 2);
          // nzuimm = {inst[12:11] -> uimm[5:4], inst[10:7] -> uimm[9:6], inst[6] -> uimm[2], inst[5] -> uimm[3]}
          // Corrected: inst[6] -> bit 2, inst[5] -> bit 3
          int uimm = (BITS(i, 12, 11) << 4) | (BITS(i, 10, 7) << 6) | (BITS(i, 6, 6) << 2) | (BITS(i, 5, 5) << 3);
          if (uimm != 0) {
              rd = 8 + rd_prime;
              src1 = R(2);
              imm = uimm;
              R(rd) = src1 + imm;
              return 0;
          }
      }
      // C.LW (010)
      if ((i & 0xe003) == 0x4000) { // 010 ... ... ... 00
          int rs1_prime = BITS(i, 9, 7);
          int rd_prime = BITS(i, 4, 2);
          // Corrected: BITS(i, 5, 5) << 6 | BITS(i, 12, 10) << 3 | BITS(i, 6, 6) << 2
          int uimm = (BITS(i, 5, 5) << 6) | (BITS(i, 12, 10) << 3) | (BITS(i, 6, 6) << 2);
          // Equivalent to LW rd', offset(rs1')
          rd = 8 + rd_prime;
          int rs1 = 8 + rs1_prime;
          src1 = R(rs1);
          imm = uimm;
          R(rd) = Mr(src1 + imm, 4);
          return 0;
      }
      // C.SW (110)
      if ((i & 0xe003) == 0xc000) { // 110 ... ... ... 00
          int rs1_prime = BITS(i, 9, 7);
          int rs2_prime = BITS(i, 4, 2);
          // Corrected: BITS(i, 5, 5) << 6 | BITS(i, 12, 10) << 3 | BITS(i, 6, 6) << 2
          int uimm = (BITS(i, 5, 5) << 6) | (BITS(i, 12, 10) << 3) | (BITS(i, 6, 6) << 2);
          // Equivalent to SW rs2', offset(rs1')
          int rs1 = 8 + rs1_prime;
          int rs2 = 8 + rs2_prime;
          src1 = R(rs1);
          src2 = R(rs2);
          imm = uimm;
          word_t addr = src1 + imm;
          if (lr_valid && (addr & ~0x3) == (lr_addr & ~0x3)) lr_valid = false;
          Mw(addr, 4, src2);
          return 0;
      }
      
      // C.ADDI (000)
      if ((i & 0xe003) == 0x0001) { // 000 ... ... ... 01
          int rd_rs1 = BITS(i, 11, 7);
          int imm_val = SEXT(BITS(i, 12, 12) << 5 | BITS(i, 6, 2), 6);
          if (rd_rs1 != 0) {
              // Equivalent to ADDI rd, rd, imm
              rd = rd_rs1;
              src1 = R(rd);
              imm = imm_val;
              R(rd) = src1 + imm;
              return 0;
          } else if (imm_val == 0) {
              // C.NOP: rd=0 and imm=0 -> no operation
              return 0;
          }
      }
      
      // C.LI (010)
      if ((i & 0xe003) == 0x4001) { // 010 ... ... ... 01
          int rd_val = BITS(i, 11, 7);
          int imm_val = SEXT(BITS(i, 12, 12) << 5 | BITS(i, 6, 2), 6);
          if (rd_val != 0) {
              // Equivalent to ADDI rd, x0, imm
              rd = rd_val;
              imm = imm_val;
              R(rd) = imm;
              return 0;
          }
      }

      // C.LUI (011)
      if ((i & 0xe003) == 0x6001) { // 011 ... ... ... 01
          int rd_val = BITS(i, 11, 7);
          int imm_val = SEXT(BITS(i, 12, 12) << 17 | BITS(i, 6, 2) << 12, 18);
          if (rd_val == 2) {
              // C.ADDI16SP: addi x2, x2, nzimm (imm is multiples of 16)
              int nzuimm = (BITS(i, 12, 12) << 9) | (BITS(i, 4, 4) << 8) | (BITS(i, 3, 3) << 7) |
                            (BITS(i, 5, 5) << 6) | (BITS(i, 2, 2) << 5) | (BITS(i, 6, 6) << 4);
              int addi16sp_raw = SEXT(nzuimm, 10);
              // Corrected: nzuimm already contains the value scaled by 16 (bits 9:4).
              // No need to shift left by 4 again.
              int addi16sp_imm = addi16sp_raw;
              src1 = R(2);
              R(2) = src1 + addi16sp_imm;
              return 0;
          } else if (rd_val != 0) {
              // Equivalent to LUI rd, imm
              rd = rd_val;
              imm = imm_val;
              R(rd) = imm;
              return 0;
          }
      }

      // C.J (101)
      if ((i & 0xe003) == 0xa001) { // 101 ... ... ... 01
          // Corrected: BITS(i, 6, 6) << 7 | BITS(i, 7, 7) << 6 -> swapped
          int offset = SEXT(BITS(i, 12, 12) << 11 | BITS(i, 8, 8) << 10 | BITS(i, 10, 9) << 8 | BITS(i, 7, 7) << 6 | BITS(i, 6, 6) << 7 | BITS(i, 2, 2) << 5 | BITS(i, 11, 11) << 4 | BITS(i, 5, 3) << 1, 12);
          // Equivalent to JAL x0, offset
          s->dnpc = s->pc + offset;
          return 0;
      }

      // C.JAL (001) [RV32]: JAL x1, offset (link to pc+2)
      if ((i & 0xe003) == 0x2001) { // 001 ... ... ... 01
          // Corrected: BITS(i, 6, 6) << 7 | BITS(i, 7, 7) << 6 -> swapped
          int offset = SEXT(BITS(i, 12, 12) << 11 | BITS(i, 8, 8) << 10 | BITS(i, 10, 9) << 8 | BITS(i, 7, 7) << 6 | BITS(i, 6, 6) << 7 | BITS(i, 2, 2) << 5 | BITS(i, 11, 11) << 4 | BITS(i, 5, 3) << 1, 12);
          R(1) = s->pc + 2;
          s->dnpc = s->pc + offset;
          return 0;
      }

      // C.BEQZ (110)
      if ((i & 0xe003) == 0xc001) { // 110 ... ... ... 01
          int rs1_prime = BITS(i, 9, 7);
          int offset = SEXT(BITS(i, 12, 12) << 8 | BITS(i, 6, 5) << 6 | BITS(i, 2, 2) << 5 | BITS(i, 11, 10) << 3 | BITS(i, 4, 3) << 1, 9);
          // Equivalent to BEQ rs1', x0, offset
          int rs1 = 8 + rs1_prime;
          src1 = R(rs1);
          if (src1 == 0) s->dnpc = s->pc + offset;
          return 0;
      }

      // C.BNEZ (111)
      if ((i & 0xe003) == 0xe001) { // 111 ... ... ... 01
          int rs1_prime = BITS(i, 9, 7);
          int offset = SEXT(BITS(i, 12, 12) << 8 | BITS(i, 6, 5) << 6 | BITS(i, 2, 2) << 5 | BITS(i, 11, 10) << 3 | BITS(i, 4, 3) << 1, 9);
          // Equivalent to BNE rs1', x0, offset
          int rs1 = 8 + rs1_prime;
          src1 = R(rs1);
          if (src1 != 0) s->dnpc = s->pc + offset;
          return 0;
      }
      
      // C.SLLI (000)
      if ((i & 0xe003) == 0x0002) { // 000 ... ... ... 10
          int rd_rs1 = BITS(i, 11, 7);
          int shamt = BITS(i, 12, 12) << 5 | BITS(i, 6, 2);
          if (rd_rs1 != 0) {
              // Equivalent to SLLI rd, rd, shamt
              rd = rd_rs1;
              src1 = R(rd);
              imm = shamt;
              R(rd) = src1 << imm;
              return 0;
          }
      }

      // C.SRLI (100, 01 quadrant): rd'=rs1'
      if ((i & 0xec03) == 0x8001) { // funct3=100, bits[11:10]=00, quadrant=01
          int rs1_prime = BITS(i, 9, 7);
          int shamt = (BITS(i, 12, 12) << 5) | BITS(i, 6, 2);
          rd = 8 + rs1_prime;
          R(rd) = (uint32_t)R(rd) >> shamt;
          return 0;
      }

      // C.SRAI (100)
      if ((i & 0xec03) == 0x8401) { // bits[11:10]=01
          int rs1_prime = BITS(i, 9, 7);
          int shamt = (BITS(i, 12, 12) << 5) | BITS(i, 6, 2);
          rd = 8 + rs1_prime;
          R(rd) = (int32_t)R(rd) >> shamt;
          return 0;
      }

      // C.ANDI (100)
      if ((i & 0xec03) == 0x8801) { // bits[11:10]=10
          int rs1_prime = BITS(i, 9, 7);
          int imm_val = SEXT((BITS(i, 12, 12) << 5) | BITS(i, 6, 2), 6);
          rd = 8 + rs1_prime;
          R(rd) = R(rd) & imm_val;
          return 0;
      }

      // C.SUB/C.XOR/C.OR/C.AND (100)
      if ((i & 0xec03) == 0x8c01) { // bits[11:10]=11
          int rd_prime = BITS(i, 9, 7);
          int rs2_prime = BITS(i, 4, 2);
          int op = BITS(i, 6, 5);
          rd = 8 + rd_prime;
          word_t a = R(rd);
          word_t b = R(8 + rs2_prime);
          switch (op) {
            case 0: R(rd) = (int32_t)a - (int32_t)b; break; // SUB
            case 1: R(rd) = a ^ b; break;                 // XOR
            case 2: R(rd) = a | b; break;                 // OR
            case 3: R(rd) = a & b; break;                 // AND
          }
          return 0;
      }

      // C.LWSP (010)
      if ((i & 0xe003) == 0x4002) { // 010 ... ... ... 10
          int rd_val = BITS(i, 11, 7);
          int uimm = (BITS(i, 3, 2) << 6) | (BITS(i, 12, 12) << 5) | (BITS(i, 6, 4) << 2);
          if (rd_val != 0) {
              // Equivalent to LW rd, offset(x2)
              rd = rd_val;
              src1 = R(2); // x2 is SP
              imm = uimm;
              R(rd) = Mr(src1 + imm, 4);
              return 0;
          }
      }

      // C.JR (100)
      if ((i & 0xf007) == 0x8002) { // 100 0 ... ... 000 10
          int rs1_val = BITS(i, 11, 7);
          int rs2_val = BITS(i, 6, 2);
          if (rs1_val != 0 && rs2_val == 0) {
              // Equivalent to JALR x0, 0(rs1)
              int rs1 = rs1_val;
              src1 = R(rs1);
              s->dnpc = src1 & ~1;
              return 0;
          }
      }

      // C.JALR (100) (link to pc+2)
      if ((i & 0xf007) == 0x9002) { // 100 1 ... ... 000 10
          int rs1_val = BITS(i, 11, 7);
          int rs2_val = BITS(i, 6, 2);
          if (rs1_val != 0 && rs2_val == 0) {
              R(1) = s->pc + 2;
              s->dnpc = R(rs1_val) & ~1;
              return 0;
          }
      }

      // C.EBREAK (100) with rs1=0 and rs2=0
      if ((i & 0xffff) == 0x9002 && BITS(i, 11, 7) == 0 && BITS(i, 6, 2) == 0) {
          NEMUTRAP(s->pc, R(10));
          return 0;
      }

      // C.MV (100)
      if ((i & 0xf003) == 0x8002) { // 100 0 ... ... ... 10
          int rs1_val = BITS(i, 11, 7);
          int rs2_val = BITS(i, 6, 2);
          if (rs1_val != 0 && rs2_val != 0) {
              // Equivalent to ADD rd, x0, rs2
              rd = rs1_val;
              int rs2 = rs2_val;
              src2 = R(rs2);
              R(rd) = src2;
              return 0;
          }
      }

      // C.ADD (100)
      if ((i & 0xf003) == 0x9002) { // 100 1 ... ... ... 10
          int rs1_rd = BITS(i, 11, 7);
          int rs2_val = BITS(i, 6, 2);
          if (rs1_rd != 0 && rs2_val != 0) {
              // Equivalent to ADD rd, rd, rs2
              rd = rs1_rd;
              int rs2 = rs2_val;
              src1 = R(rd);
              src2 = R(rs2);
              R(rd) = src1 + src2;
              return 0;
          }
      }

      // C.SWSP (110)
      if ((i & 0xe003) == 0xc002) { // 110 ... ... ... 10
          int rs2_val = BITS(i, 6, 2);
          int uimm = (BITS(i, 8, 7) << 6) | (BITS(i, 12, 9) << 2);
          // Equivalent to SW rs2, offset(x2)
          int rs2 = rs2_val;
          src1 = R(2); // x2 is SP
          src2 = R(rs2);
          imm = uimm;
          word_t addr = src1 + imm;
          if (lr_valid && (addr & ~0x3) == (lr_addr & ~0x3)) lr_valid = false;
          Mw(addr, 4, src2);
          return 0;
      }

      // If we reach here, it's an unimplemented compressed instruction
      INV(s->pc);
      return 0;
  }

  INSTPAT_START();

  // ebreak 指令，用于触发一个环境断点异常
  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0

  //
  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , R, R(rd) = src1 + src2);
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , R, R(rd) = src1 - src2);
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , R, R(rd) = src1 ^ src2);
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , R, R(rd) = src1 | src2);
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , R, R(rd) = src1 & src2);
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , R, R(rd) = src1 < src2 ? 1 : 0);
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , R, R(rd) = (int32_t)src1 < (int32_t)src2 ? 1 : 0);


  //
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, R(rd) = (int32_t)src1 >> imm );
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , R, R(rd) = (int32_t)src1 >> (src2 & 0x1f));
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl    , R, R(rd) = (uint32_t) src1 >> (src2 & 0x1f));
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , R, R(rd) = (uint32_t) src1 << (src2 & 0x1f));
  INSTPAT("0000000 ????? ????? 101 ????? 00100 11", srli   , I, R(rd) = (uint32_t) src1 >> imm);
  INSTPAT("0000000 ????? ????? 001 ????? 00100 11", slli   , I, R(rd) = (uint32_t) src1 << imm);


  // multiply and divide
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul  , R, R(rd) = (int32_t)src1 * (int32_t)src2);
  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh , R, R(rd) = ((int64_t)(int32_t)src1 * (int64_t)(int32_t)src2) >> 32);
  INSTPAT("0000001 ????? ????? 010 ????? 01100 11", mulhsu , R, R(rd) = ((int64_t)(int32_t)src1 * (uint64_t)(uint32_t)src2) >> 32);
  INSTPAT("0000001 ????? ????? 011 ????? 01100 11", mulhu  , R, R(rd) = ((uint64_t)(uint32_t)src1 * (uint64_t)(uint32_t)src2) >> 32);
  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div  , R, R(rd) = ((int32_t)src2 == 0) ? -1 : (((int32_t)src1 == (int32_t)0x80000000 && (int32_t)src2 == -1) ? (int32_t)0x80000000 : (int32_t)src1 / (int32_t)src2));
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu , R, R(rd) = ((uint32_t)src2 == 0) ? 0xFFFFFFFFu : (uint32_t)src1 / (uint32_t)src2);
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem  , R, R(rd) = ((int32_t)src2 == 0) ? (int32_t)src1 : (((int32_t)src1 == (int32_t)0x80000000 && (int32_t)src2 == -1) ? 0 : (int32_t)src1 % (int32_t)src2));
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu , R, R(rd) = ((uint32_t)src2 == 0) ? (uint32_t)src1 : (uint32_t)src1 % (uint32_t)src2);
    // 
  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = src1 + imm);
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm);
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & imm);
  INSTPAT("??????? ????? ????? 110 ????? 00100 11", ori    , I, R(rd) = src1 | (word_t)imm);
  INSTPAT("??????? ????? ????? 010 ????? 00100 11", slti   , I, R(rd) = (int32_t)src1 < (int32_t)imm ? 1 : 0);
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, R(rd) = (uint32_t)src1 < (uint32_t)imm ? 1 : 0);


  //
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr(src1 + imm, 4));INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb     , I, R(rd) = SEXT(Mr(src1 + imm, 1), 8));
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd) = SEXT(Mr(src1 + imm, 2), 16));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd) = Mr(src1 + imm, 2));
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr(src1 + imm, 1));
  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, if (lr_valid && (lr_addr & ~0x3) == ((src1 + imm) & ~0x3)) lr_valid = false; Mw(src1 + imm, 4, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, if (lr_valid && (lr_addr & ~0x3) == ((src1 + imm) & ~0x3)) lr_valid = false; Mw(src1 + imm, 2, src2));
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, if (lr_valid && (lr_addr & ~0x3) == ((src1 + imm) & ~0x3)) lr_valid = false; Mw(src1 + imm, 1, src2 & 0xff));

  //

  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B, if (src1 == src2) s->dnpc = s->pc + imm);
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B, if (src1 != src2) s->dnpc = s->pc + imm); 
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B, if ((int32_t)src1 <  (int32_t)src2) s->dnpc = s->pc + imm);
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B, if ((int32_t)src1 >= (int32_t)src2) s->dnpc = s->pc + imm);
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B, if (src1 < src2) s->dnpc = s->pc + imm);
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B, if (src1 >= src2) s->dnpc = s->pc + imm);
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, R(rd) = s->pc + 4, s->dnpc = (src1 + imm) & ~1);
  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J, R(rd) = s->pc + 4, s->dnpc = s->pc + imm);
  
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);
  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui    , U, R(rd) = imm);

  // RV32A Extension (word, funct3 = 010)

  INSTPAT("00010?? 00000 ????? 010 ????? 01011 11", lr.w   , R, R(rd) = Mr(src1, 4); lr_valid = true; lr_addr = src1);
    INSTPAT("00011?? ????? ????? 010 ????? 01011 11", sc.w   , R, if (lr_valid && lr_addr == src1) { Mw(src1, 4, src2); R(rd) = 0; } else { R(rd) = 1; } lr_valid = false;);
    INSTPAT("00001?? ????? ????? 010 ????? 01011 11", amoswap.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; Mw(src1, 4, src2); R(rd) = t);
    INSTPAT("00000?? ????? ????? 010 ????? 01011 11", amoadd.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; Mw(src1, 4, t + src2); R(rd) = t);
    INSTPAT("00100?? ????? ????? 010 ????? 01011 11", amoxor.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; Mw(src1, 4, t ^ src2); R(rd) = t);
    INSTPAT("01000?? ????? ????? 010 ????? 01011 11", amoor.w,  R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; Mw(src1, 4, t | src2); R(rd) = t);
    INSTPAT("01100?? ????? ????? 010 ????? 01011 11", amoand.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; Mw(src1, 4, t & src2); R(rd) = t);
    INSTPAT("10000?? ????? ????? 010 ????? 01011 11", amomin.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; word_t nv = ((int32_t)t < (int32_t)src2) ? t : src2; Mw(src1, 4, nv); R(rd) = t);
    INSTPAT("10100?? ????? ????? 010 ????? 01011 11", amomax.w, R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; word_t nv = ((int32_t)t > (int32_t)src2) ? t : src2; Mw(src1, 4, nv); R(rd) = t);
    INSTPAT("11000?? ????? ????? 010 ????? 01011 11", amominu.w,R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; word_t nv = ((uint32_t)t < (uint32_t)src2) ? t : src2; Mw(src1, 4, nv); R(rd) = t);
    INSTPAT("11100?? ????? ????? 010 ????? 01011 11", amomaxu.w,R, word_t t = Mr(src1, 4); if (lr_valid && lr_addr == src1) lr_valid = false; word_t nv = ((uint32_t)t > (uint32_t)src2) ? t : src2; Mw(src1, 4, nv); R(rd) = t);

  INSTPAT("??????? ????? ????? 000 ????? 00011 11", fence  , N, );
  INSTPAT("??????? ????? ????? 001 ????? 00011 11", fence.i, N, );

  //
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));
  INSTPAT_END();

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  s->isa.inst = inst_fetch(&s->snpc);
  return decode_exec(s);
}
