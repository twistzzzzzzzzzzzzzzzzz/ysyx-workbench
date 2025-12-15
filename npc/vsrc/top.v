`include "IF.v"
`include "RegFile.v"
`include "EX.v"

module top(
  input clk,
  input rst
);

  wire [31:0] pc;
  wire [31:0] inst;
  wire [31:0] rdata1;
  wire [31:0] rdata2;
  wire [31:0] ex_result;
  wire [4:0]  ex_rd;
  wire        ex_wen;

  // Instruction Fetch
  IF if_stage (
    .clk(clk),
    .rst(rst),
    .pc(pc),
    .inst(inst)
  );

  // Register File
  RegFile reg_file (
    .clk(clk),
    .raddr1(inst[19:15]),
    .rdata1(rdata1),
    .raddr2(inst[24:20]),
    .rdata2(rdata2),
    .wen(ex_wen),
    .waddr(ex_rd),
    .wdata(ex_result)
  );

  // Execute
  EX ex_stage (
    .inst(inst),
    .pc(pc),
    .rdata1(rdata1),
    .rdata2(rdata2),
    .result(ex_result),
    .rd(ex_rd),
    .wen(ex_wen)
  );

  // In a real CPU, we would have more stages (MEM, WB)
  // For now, the output of EX is directly written back.

  // For debugging, you can add display statements here
  always @(posedge clk) begin
    if (!rst) begin
      $display("PC: %h, Inst: %h, rdata1: %h, rdata2: %h, wen: %b, waddr: %d, wdata: %h",
        pc, inst, rdata1, rdata2, ex_wen, ex_rd, ex_result);
    end
  end

endmodule
