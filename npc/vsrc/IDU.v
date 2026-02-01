module IDU(
    input [31:0] inst,
    //input [31:0] pc,
    output reg gpr_wen,
    output reg mem_wen,
    output reg mem_ren,
    output reg gpr_ren,
    output reg [31:0] imm,
    output reg [4:0] rs1,
    output reg [4:0] rs2, 
    output reg [4:0] rd,
    output reg [6:0] opcode,
    output reg [2:0] func3,
    output reg inst_valid
   
);


reg [2:0] inst_type;

parameter I_TYPE = 3'b000;
parameter R_TYPE = 3'b001;
parameter U_TYPE = 3'b010;
parameter J_TYPE = 3'b100;
parameter S_TYPE = 3'b101;
parameter B_TYPE = 3'b110;






always @ (*)begin
    inst_valid = 1'b0;
    gpr_wen = 1'b0;
    mem_wen = 1'b0;
    mem_ren = 1'b0;
    inst_type = 3'b000;
    opcode = 7'b0;
    func3 = 3'b0;
    imm = 32'b0;
    rs1 = 5'b0;
    rs2 = 5'b0;
    rd = 5'b0;

   casez (inst)
/*----------------------------I_TYPE-------------------------------*/

//ebreak
    32'b0000000_00001_00000_000_00000_1110011: begin inst_valid = 1'b1; gpr_wen = 1'b0; inst_type = 3'b000; opcode = 7'b1110011; func3 = 3'b000; end
//addi
    32'b???????_?????_?????_000_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b000; end
//xori
    32'b???????_?????_?????_100_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b100; end

//jalr 
    32'b???????_?????_?????_???_?????_1100111: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b1100111; func3 = 3'b000; end

//srli
    32'b0000000_?????_?????_101_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b101; end
//slli
    32'b0000000_?????_?????_001_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b001; end

//lw
    32'b???????_?????_?????_010_?????_0000011: begin inst_valid = 1'b1; gpr_wen = 1'b1; mem_ren = 1'b1; inst_type = 3'b000; opcode = 7'b0000011; func3 = 3'b010; end
//lb
    32'b???????_?????_?????_000_?????_0000011: begin inst_valid = 1'b1; gpr_wen = 1'b1; mem_ren = 1'b1; inst_type = 3'b000; opcode = 7'b0000011; func3 = 3'b000; end
//lhu
    32'b???????_?????_?????_101_?????_0000011: begin inst_valid = 1'b1; gpr_wen = 1'b1; mem_ren = 1'b1; inst_type = 3'b000; opcode = 7'b0000011; func3 = 3'b101; end
//lbu
    32'b???????_?????_?????_100_?????_0000011: begin inst_valid = 1'b1; gpr_wen = 1'b1; mem_ren = 1'b1; inst_type = 3'b000; opcode = 7'b0000011; func3 = 3'b100; end
//lh
    32'b???????_?????_?????_001_?????_0000011: begin inst_valid = 1'b1; gpr_wen = 1'b1; mem_ren = 1'b1; inst_type = 3'b000; opcode = 7'b0000011; func3 = 3'b001; end



//sltiu
    32'b???????_?????_?????_011_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b011; end
//slti
    32'b???????_?????_?????_010_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b010; end
//srai
    32'b0100000_?????_?????_101_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b101; end
//andi
    32'b???????_?????_?????_111_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b111; end
//ori
    32'b???????_?????_?????_110_?????_0010011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b000; opcode = 7'b0010011; func3 = 3'b110; end
/*----------------------------R_TYPE-------------------------------*/
//sll
    32'b0000000_?????_?????_001_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b001; end
//add
    32'b0000000_?????_?????_000_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b000; end
//sub
    32'b0100000_?????_?????_000_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b000; end
//sltu
    32'b0000000_?????_?????_011_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b011; end
//slt
    32'b0000000_?????_?????_010_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b010; end
//sra
    32'b0100000_?????_?????_101_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b101; end
//srl
    32'b0000000_?????_?????_101_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b101; end
//xor
    32'b0000000_?????_?????_100_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b100; end
//or
    32'b0000000_?????_?????_110_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b110; end
//and
    32'b0000000_?????_?????_111_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b111; end
//div
    //32'b0000001_?????_?????_100_?????_0110011: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b001; opcode = 7'b0110011; func3 = 3'b100; end

/*----------------------------U_TYPE-------------------------------*/
//auipc
    32'b???????_?????_?????_???_?????_0010111: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b010; opcode = 7'b0010111; end
//lui
    32'b???????_?????_?????_???_?????_0110111: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b010; opcode = 7'b0110111; end
/*----------------------------J_TYPE-------------------------------*/

//jal
    32'b???????_?????_?????_???_?????_1101111: begin inst_valid = 1'b1; gpr_wen = 1'b1; inst_type = 3'b100; opcode = 7'b1101111; end

/*----------------------------S_TYPE-------------------------------*/

//sw
    32'b???????_?????_?????_010_?????_0100011: begin inst_valid = 1'b1; mem_wen = 1'b1; inst_type = 3'b101; opcode = 7'b0100011; func3 = 3'b010; end
//sh
    32'b???????_?????_?????_001_?????_0100011: begin inst_valid = 1'b1; mem_wen = 1'b1; inst_type = 3'b101; opcode = 7'b0100011; func3 = 3'b001; end
//sb
    32'b???????_?????_?????_000_?????_0100011: begin inst_valid = 1'b1; mem_wen = 1'b1; inst_type = 3'b101; opcode = 7'b0100011; func3 = 3'b000; end


/*----------------------------B_TYPE-------------------------------*/

//beq
    32'b???????_?????_?????_000_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b000; end

//bne
    32'b???????_?????_?????_001_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b001; end

//bge
    32'b???????_?????_?????_101_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b101; end

//bgeu
    32'b???????_?????_?????_111_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b111; end

//blt
    32'b???????_?????_?????_100_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b100; end
//bltu
    32'b???????_?????_?????_110_?????_1100011: begin inst_valid = 1'b1; inst_type = 3'b110; opcode = 7'b1100011; func3 = 3'b110; end



   
    default : begin

       inst_valid = 1'b0;

    end
   endcase 

    case (inst_type)

        I_TYPE: begin imm = {{20{inst[31]}}, inst[31:20]}; rs1 = inst[19:15]; rd = inst[11:7]; end
        R_TYPE: begin rs1 = inst[19:15]; rs2 = inst[24:20]; rd = inst[11:7]; end
        U_TYPE: begin imm = {inst[31:12], 12'b0}; rd = inst[11:7]; end
        J_TYPE: begin imm = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0}; rd = inst[11:7]; end
        S_TYPE: begin 
            imm = {{20{inst[31]}}, inst[31:25], inst[11:7]}; 
            rs1 = inst[19:15]; 
            rs2 = inst[24:20]; 
        end
        B_TYPE: begin 
            imm = {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0}; 
            rs1 = inst[19:15]; 
            rs2 = inst[24:20]; 
        end
        default:begin imm = 32'b0; rs1 = 5'b0; rd = 5'b0; end
    endcase


/*----------------ftrace-------------------------*/



end

endmodule