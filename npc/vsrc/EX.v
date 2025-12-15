/* verilator lint_off UNUSEDSIGNAL */
import "DPI-C" function void npc_trap(input int code);
module EX(
  input  [31:0] inst,
  input  [31:0] pc,
  input  [31:0] rdata1,
  input  [31:0] rdata2,
  output [31:0] result,
  output [4:0]  rd,
  output        wen
);
/* verilator lint_on UNUSEDSIGNAL */

  // Decode immediate for I-type instructions
  wire [31:0] imm_i = {{21{inst[31]}}, inst[30:20]};
  
  // For now, we only handle ADDI
  // Opcode for ADDI is 0010011
  wire is_addi = (inst[6:0] == 7'b0010011);

  // ebreak instruction (RISC-V): 32'h0010_0073
  wire is_ebreak = (inst == 32'h00100073);

  // ALU operation
  assign result = rdata1 + imm_i;

  // Destination register
  assign rd = inst[11:7];

  // Write enable for register file
  assign wen = is_addi && (rd != 5'b0);

  // Notify simulator to finish on ebreak
  always @(*) begin
    if (is_ebreak) begin
      npc_trap(0);
    end
  end

endmodule
