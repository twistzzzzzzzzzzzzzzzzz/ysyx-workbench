module top(
    input clk,
    input rst,
    output reg [31:0] pc,
    output [31:0] inst,
    output [31:0] res,
    output [31:0] x0, x1, x2, x3, x10
);
//pc

wire [31:0] dnpc;


always @(posedge clk) begin
    if (rst) begin
      pc <= 32'h8000_0000;
    end else begin
      pc <= dnpc;
    end
end



IFU inst_fetch(
    .clk(clk),
    .pc (pc),
    .rst(rst),
    .inst(inst)

);

wire wen;

wire [31:0] imm;


wire [4:0]  raddr1;
wire [4:0]  raddr2;
wire [31:0] rdata1;
wire [31:0] rdata2;

wire [4:0]  rd;
wire [6:0]  opcode;
wire [2:0]  func3;





IDU inst_decode(    
    .wen    (wen),
    .inst   (inst),
    .imm    (imm),
    .raddr1 (raddr1),
    .raddr2 (raddr2),
    .rd     (rd),
    .opcode (opcode),
    .func3  (func3)
);

EXU inst_execute(
    .clk    (clk),
    .pc     (pc),
    .imm    (imm),
    .rdata1 (rdata1),
    .rdata2 (rdata2),
    .res    (res),
    .opcode (opcode),
    .func3  (func3),
    .dnpc   (dnpc)
);

GPR gpr(
    .clk    (clk),
    .wen    (wen),
    .raddr1 (raddr1),
    .raddr2 (raddr2),
    .wdata  (res),
    .waddr  (rd),
    .rdata1 (rdata1),
    .rdata2 (rdata2),
    .x0     (x0),
    .x1     (x1),
    .x2     (x2),
    .x3     (x3),
    .x10    (x10)
);


endmodule
