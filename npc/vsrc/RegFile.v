module RegFile(
  input  clk,
  input  [4:0] raddr1,
  output [31:0] rdata1,
  input  [4:0] raddr2,
  output [31:0] rdata2,

  input  wen,
  input  [4:0] waddr,
  input  [31:0] wdata
);

  reg [31:0] rf[31:0];

  // Write port
  always @(posedge clk) begin
    if (wen && waddr != 5'b0) begin
      rf[waddr] <= wdata;
    end
  end

  // Read port 1
  assign rdata1 = (raddr1 == 5'b0) ? 32'b0 : rf[raddr1];

  // Read port 2
  assign rdata2 = (raddr2 == 5'b0) ? 32'b0 : rf[raddr2];

endmodule
