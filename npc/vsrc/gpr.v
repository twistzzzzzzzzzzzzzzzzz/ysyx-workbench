module GPR(
  	input clk,
  	input wen,

  	input [4:0] waddr,
  	input [31:0] wdata,
  	input [4:0] raddr1,
  	input [4:0] raddr2,
  	output [31:0] rdata1,
  	output [31:0] rdata2,
	output [31:0] x10


);


import "DPI-C" function void set_gpr_ptr(input logic [31:0] a[]);
initial begin
    // 这里的 x 必须对应你定义的 reg [31:0] x [31:0];
    set_gpr_ptr(x[0]); 
    $display("Verilog side: GPR pointer sent to C."); // 加一行这个调试，看看屏幕有没有输出
end


  	reg [31:0] x [31:0];

  // r(x0) = 0
  	assign rdata1 = (raddr1 == 5'b0) ? 32'b0 : x[raddr1];
  	assign rdata2 = (raddr2 == 5'b0) ? 32'b0 : x[raddr2];
	assign x10 = x[10];

  	always @(posedge clk) begin
		if (wen && (waddr != 5'b0)) begin
      		x[waddr] <= wdata;
    	end
  	end
endmodule