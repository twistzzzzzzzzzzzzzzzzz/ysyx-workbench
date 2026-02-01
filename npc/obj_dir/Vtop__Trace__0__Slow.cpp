// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+54,"clk", false,-1);
    tracep->declBit(c+55,"rst", false,-1);
    tracep->declBus(c+56,"pc", false,-1, 31,0);
    tracep->declBus(c+57,"inst", false,-1, 31,0);
    tracep->declBus(c+58,"x10", false,-1, 31,0);
    tracep->declBus(c+59,"rdata1", false,-1, 31,0);
    tracep->declBus(c+60,"rdata2", false,-1, 31,0);
    tracep->declBus(c+61,"imm", false,-1, 31,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+54,"clk", false,-1);
    tracep->declBit(c+55,"rst", false,-1);
    tracep->declBus(c+56,"pc", false,-1, 31,0);
    tracep->declBus(c+57,"inst", false,-1, 31,0);
    tracep->declBus(c+58,"x10", false,-1, 31,0);
    tracep->declBus(c+59,"rdata1", false,-1, 31,0);
    tracep->declBus(c+60,"rdata2", false,-1, 31,0);
    tracep->declBus(c+61,"imm", false,-1, 31,0);
    tracep->declBus(c+1,"dnpc", false,-1, 31,0);
    tracep->declBus(c+2,"mem_wdata", false,-1, 31,0);
    tracep->declBus(c+3,"wmask", false,-1, 3,0);
    tracep->declBus(c+4,"rmask", false,-1, 3,0);
    tracep->declBus(c+5,"gpr_wdata", false,-1, 31,0);
    tracep->declBus(c+57,"mem_inst", false,-1, 31,0);
    tracep->declBus(c+6,"mem_rdata", false,-1, 31,0);
    tracep->declBus(c+7,"mem_waddr", false,-1, 31,0);
    tracep->declBus(c+8,"mem_raddr", false,-1, 31,0);
    tracep->declBit(c+11,"gpr_wen", false,-1);
    tracep->declBit(c+63,"gpr_ren", false,-1);
    tracep->declBit(c+12,"mem_wen", false,-1);
    tracep->declBit(c+13,"mem_ren", false,-1);
    tracep->declBus(c+14,"raddr1", false,-1, 4,0);
    tracep->declBus(c+15,"raddr2", false,-1, 4,0);
    tracep->declBit(c+16,"inst_valid", false,-1);
    tracep->declBus(c+17,"opcode", false,-1, 6,0);
    tracep->declBus(c+18,"func3", false,-1, 2,0);
    tracep->declBus(c+19,"gpr_waddr", false,-1, 4,0);
    tracep->declBus(c+64,"gpr_rdata", false,-1, 31,0);
    tracep->declBus(c+65,"gpr_raddr", false,-1, 4,0);
    tracep->pushNamePrefix("gpr ");
    tracep->declBit(c+54,"clk", false,-1);
    tracep->declBit(c+11,"wen", false,-1);
    tracep->declBus(c+19,"waddr", false,-1, 4,0);
    tracep->declBus(c+5,"wdata", false,-1, 31,0);
    tracep->declBus(c+14,"raddr1", false,-1, 4,0);
    tracep->declBus(c+15,"raddr2", false,-1, 4,0);
    tracep->declBus(c+59,"rdata1", false,-1, 31,0);
    tracep->declBus(c+60,"rdata2", false,-1, 31,0);
    tracep->declBus(c+58,"x10", false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+20+i*1,"x", true,(i+0), 31,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inst_decode ");
    tracep->declBus(c+57,"inst", false,-1, 31,0);
    tracep->declBit(c+11,"gpr_wen", false,-1);
    tracep->declBit(c+12,"mem_wen", false,-1);
    tracep->declBit(c+13,"mem_ren", false,-1);
    tracep->declBit(c+63,"gpr_ren", false,-1);
    tracep->declBus(c+61,"imm", false,-1, 31,0);
    tracep->declBus(c+14,"rs1", false,-1, 4,0);
    tracep->declBus(c+15,"rs2", false,-1, 4,0);
    tracep->declBus(c+19,"rd", false,-1, 4,0);
    tracep->declBus(c+17,"opcode", false,-1, 6,0);
    tracep->declBus(c+18,"func3", false,-1, 2,0);
    tracep->declBit(c+16,"inst_valid", false,-1);
    tracep->declBus(c+52,"inst_type", false,-1, 2,0);
    tracep->declBus(c+66,"I_TYPE", false,-1, 2,0);
    tracep->declBus(c+67,"R_TYPE", false,-1, 2,0);
    tracep->declBus(c+68,"U_TYPE", false,-1, 2,0);
    tracep->declBus(c+69,"J_TYPE", false,-1, 2,0);
    tracep->declBus(c+70,"S_TYPE", false,-1, 2,0);
    tracep->declBus(c+71,"B_TYPE", false,-1, 2,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inst_execute ");
    tracep->declBit(c+54,"clk", false,-1);
    tracep->declBus(c+56,"pc", false,-1, 31,0);
    tracep->declBus(c+57,"inst", false,-1, 31,0);
    tracep->declBus(c+61,"imm", false,-1, 31,0);
    tracep->declBus(c+59,"rs1", false,-1, 31,0);
    tracep->declBus(c+60,"rs2", false,-1, 31,0);
    tracep->declBus(c+6,"mem_rdata", false,-1, 31,0);
    tracep->declBus(c+17,"opcode", false,-1, 6,0);
    tracep->declBus(c+18,"func3", false,-1, 2,0);
    tracep->declBit(c+62,"inst_valid", false,-1);
    tracep->declBus(c+1,"dnpc", false,-1, 31,0);
    tracep->declBus(c+5,"gpr_wdata", false,-1, 31,0);
    tracep->declBus(c+65,"gpr_raddr", false,-1, 4,0);
    tracep->declBus(c+64,"gpr_rdata", false,-1, 31,0);
    tracep->declBus(c+2,"mem_wdata", false,-1, 31,0);
    tracep->declBus(c+7,"mem_waddr", false,-1, 31,0);
    tracep->declBus(c+8,"mem_raddr", false,-1, 31,0);
    tracep->declBus(c+3,"wmask", false,-1, 3,0);
    tracep->declBus(c+4,"rmask", false,-1, 3,0);
    tracep->pushNamePrefix("unnamedblk1 ");
    tracep->declBus(c+9,"snpc", false,-1, 31,0);
    tracep->declBus(c+10,"alu_res", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("inst_fetch ");
    tracep->declBus(c+57,"mem_inst", false,-1, 31,0);
    tracep->declBus(c+57,"inst", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("ram ");
    tracep->declBit(c+54,"clk", false,-1);
    tracep->declBus(c+56,"inst_addr", false,-1, 31,0);
    tracep->declBus(c+57,"inst_data", false,-1, 31,0);
    tracep->declBus(c+8,"raddr", false,-1, 31,0);
    tracep->declBus(c+6,"rdata", false,-1, 31,0);
    tracep->declBus(c+4,"rmask", false,-1, 3,0);
    tracep->declBus(c+7,"waddr", false,-1, 31,0);
    tracep->declBus(c+2,"wdata", false,-1, 31,0);
    tracep->declBus(c+3,"wmask", false,-1, 3,0);
    tracep->declBit(c+12,"wen", false,-1);
    tracep->declBit(c+13,"ren", false,-1);
    tracep->declBus(c+53,"inst_temp", false,-1, 31,0);
    tracep->declBus(c+6,"rdata_temp", false,-1, 31,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->top__DOT__dnpc),32);
    bufp->fullIData(oldp+2,(vlSelf->top__DOT__mem_wdata),32);
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__wmask),4);
    bufp->fullCData(oldp+4,(vlSelf->top__DOT__rmask),4);
    bufp->fullIData(oldp+5,(vlSelf->top__DOT__gpr_wdata),32);
    bufp->fullIData(oldp+6,(vlSelf->top__DOT__ram__DOT__rdata_temp),32);
    bufp->fullIData(oldp+7,(vlSelf->top__DOT__mem_waddr),32);
    bufp->fullIData(oldp+8,(vlSelf->top__DOT__mem_raddr),32);
    bufp->fullIData(oldp+9,(vlSelf->top__DOT__inst_execute__DOT__unnamedblk1__DOT__snpc),32);
    bufp->fullIData(oldp+10,(vlSelf->top__DOT__inst_execute__DOT__unnamedblk1__DOT__alu_res),32);
    bufp->fullBit(oldp+11,(vlSelf->top__DOT__gpr_wen));
    bufp->fullBit(oldp+12,(vlSelf->top__DOT__mem_wen));
    bufp->fullBit(oldp+13,(vlSelf->top__DOT__mem_ren));
    bufp->fullCData(oldp+14,(vlSelf->top__DOT__raddr1),5);
    bufp->fullCData(oldp+15,(vlSelf->top__DOT__raddr2),5);
    bufp->fullBit(oldp+16,(vlSelf->top__DOT__inst_valid));
    bufp->fullCData(oldp+17,(vlSelf->top__DOT__opcode),7);
    bufp->fullCData(oldp+18,(vlSelf->top__DOT__func3),3);
    bufp->fullCData(oldp+19,(vlSelf->top__DOT__gpr_waddr),5);
    bufp->fullIData(oldp+20,(vlSelf->top__DOT__gpr__DOT__x[0]),32);
    bufp->fullIData(oldp+21,(vlSelf->top__DOT__gpr__DOT__x[1]),32);
    bufp->fullIData(oldp+22,(vlSelf->top__DOT__gpr__DOT__x[2]),32);
    bufp->fullIData(oldp+23,(vlSelf->top__DOT__gpr__DOT__x[3]),32);
    bufp->fullIData(oldp+24,(vlSelf->top__DOT__gpr__DOT__x[4]),32);
    bufp->fullIData(oldp+25,(vlSelf->top__DOT__gpr__DOT__x[5]),32);
    bufp->fullIData(oldp+26,(vlSelf->top__DOT__gpr__DOT__x[6]),32);
    bufp->fullIData(oldp+27,(vlSelf->top__DOT__gpr__DOT__x[7]),32);
    bufp->fullIData(oldp+28,(vlSelf->top__DOT__gpr__DOT__x[8]),32);
    bufp->fullIData(oldp+29,(vlSelf->top__DOT__gpr__DOT__x[9]),32);
    bufp->fullIData(oldp+30,(vlSelf->top__DOT__gpr__DOT__x[10]),32);
    bufp->fullIData(oldp+31,(vlSelf->top__DOT__gpr__DOT__x[11]),32);
    bufp->fullIData(oldp+32,(vlSelf->top__DOT__gpr__DOT__x[12]),32);
    bufp->fullIData(oldp+33,(vlSelf->top__DOT__gpr__DOT__x[13]),32);
    bufp->fullIData(oldp+34,(vlSelf->top__DOT__gpr__DOT__x[14]),32);
    bufp->fullIData(oldp+35,(vlSelf->top__DOT__gpr__DOT__x[15]),32);
    bufp->fullIData(oldp+36,(vlSelf->top__DOT__gpr__DOT__x[16]),32);
    bufp->fullIData(oldp+37,(vlSelf->top__DOT__gpr__DOT__x[17]),32);
    bufp->fullIData(oldp+38,(vlSelf->top__DOT__gpr__DOT__x[18]),32);
    bufp->fullIData(oldp+39,(vlSelf->top__DOT__gpr__DOT__x[19]),32);
    bufp->fullIData(oldp+40,(vlSelf->top__DOT__gpr__DOT__x[20]),32);
    bufp->fullIData(oldp+41,(vlSelf->top__DOT__gpr__DOT__x[21]),32);
    bufp->fullIData(oldp+42,(vlSelf->top__DOT__gpr__DOT__x[22]),32);
    bufp->fullIData(oldp+43,(vlSelf->top__DOT__gpr__DOT__x[23]),32);
    bufp->fullIData(oldp+44,(vlSelf->top__DOT__gpr__DOT__x[24]),32);
    bufp->fullIData(oldp+45,(vlSelf->top__DOT__gpr__DOT__x[25]),32);
    bufp->fullIData(oldp+46,(vlSelf->top__DOT__gpr__DOT__x[26]),32);
    bufp->fullIData(oldp+47,(vlSelf->top__DOT__gpr__DOT__x[27]),32);
    bufp->fullIData(oldp+48,(vlSelf->top__DOT__gpr__DOT__x[28]),32);
    bufp->fullIData(oldp+49,(vlSelf->top__DOT__gpr__DOT__x[29]),32);
    bufp->fullIData(oldp+50,(vlSelf->top__DOT__gpr__DOT__x[30]),32);
    bufp->fullIData(oldp+51,(vlSelf->top__DOT__gpr__DOT__x[31]),32);
    bufp->fullCData(oldp+52,(vlSelf->top__DOT__inst_decode__DOT__inst_type),3);
    bufp->fullIData(oldp+53,(vlSelf->top__DOT__ram__DOT__inst_temp),32);
    bufp->fullBit(oldp+54,(vlSelf->clk));
    bufp->fullBit(oldp+55,(vlSelf->rst));
    bufp->fullIData(oldp+56,(vlSelf->pc),32);
    bufp->fullIData(oldp+57,(vlSelf->inst),32);
    bufp->fullIData(oldp+58,(vlSelf->x10),32);
    bufp->fullIData(oldp+59,(vlSelf->rdata1),32);
    bufp->fullIData(oldp+60,(vlSelf->rdata2),32);
    bufp->fullIData(oldp+61,(vlSelf->imm),32);
    bufp->fullBit(oldp+62,(((IData)(vlSelf->rst) | (IData)(vlSelf->top__DOT__inst_valid))));
    bufp->fullBit(oldp+63,(vlSelf->top__DOT__gpr_ren));
    bufp->fullIData(oldp+64,(vlSelf->top__DOT__gpr_rdata),32);
    bufp->fullCData(oldp+65,(vlSelf->top__DOT__gpr_raddr),5);
    bufp->fullCData(oldp+66,(0U),3);
    bufp->fullCData(oldp+67,(1U),3);
    bufp->fullCData(oldp+68,(2U),3);
    bufp->fullCData(oldp+69,(4U),3);
    bufp->fullCData(oldp+70,(5U),3);
    bufp->fullCData(oldp+71,(6U),3);
}
