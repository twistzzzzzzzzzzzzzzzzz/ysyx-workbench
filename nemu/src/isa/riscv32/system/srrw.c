
#include "../local-include/reg.h"
#include "../include/isa-def.h"

extern MUXDEF(CONFIG_RV64, riscv64_CPU_state, riscv32_CPU_state) cpu;


word_t csr_read(word_t csr_addr) {
  switch (csr_addr) {
    case 0x300: return cpu.mstatus;
    case 0x305: return cpu.mtvec;
    case 0x341: return cpu.mepc;
    case 0x342: return cpu.mcause;
    default: panic("Unsupported CSR read: 0x%08x", csr_addr);
  }
}

void csr_write(uint32_t addr, word_t data) {
  switch (addr) {
    case 0x300: cpu.mstatus = data; break;
    case 0x305: cpu.mtvec = data;   break;
    case 0x341: cpu.mepc = data;    break;
    case 0x342: cpu.mcause = data;  break;
    default: panic("Unsupported CSR write: 0x%03x", addr);
  }
  // 确保这里没有 return 语句，或者只是 return;
}