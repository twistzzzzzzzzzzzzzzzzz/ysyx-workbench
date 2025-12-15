module IF(
  input  clk,
  input  rst,
  output [31:0] pc,
  output [31:0] inst
);

  reg [31:0] _pc;

  assign pc = _pc;

  // Instruction memory (a simple ROM)
  reg [31:0] imem [0:7];

  initial begin
    // addi t0, zero, 1
    imem[0] = 32'h00100293;
    // addi t1, zero, 2
    imem[1] = 32'h00200313;
    // addi t2, t0, 3
    imem[2] = 32'h00328393;
    // addi t3, t1, 4
    imem[3] = 32'h00430413;
    // addi t0, t0, 5
    imem[4] = 32'h00528293;
    // addi t1, t1, -1
    imem[5] = 32'hfff30313;
    // addi zero, zero, 1 // should have no effect
    imem[6] = 32'h00100073;
    // ebreak
    imem[7] = 32'h00000000; // NOP
  end

  assign inst = imem[(_pc - 32'h80000000) >> 2];

  always @(posedge clk) begin
    if (rst) begin
      _pc <= 32'h80000000;
    end else begin
      _pc <= _pc + 4;
    end
  end

endmodule
