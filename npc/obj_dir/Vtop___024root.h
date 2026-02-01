// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*3:0*/ top__DOT__wmask;
    CData/*3:0*/ top__DOT__rmask;
    CData/*0:0*/ top__DOT__gpr_wen;
    CData/*0:0*/ top__DOT__mem_wen;
    CData/*0:0*/ top__DOT__mem_ren;
    CData/*4:0*/ top__DOT__raddr1;
    CData/*4:0*/ top__DOT__raddr2;
    CData/*0:0*/ top__DOT__inst_valid;
    CData/*6:0*/ top__DOT__opcode;
    CData/*2:0*/ top__DOT__func3;
    CData/*4:0*/ top__DOT__gpr_waddr;
    CData/*2:0*/ top__DOT__inst_decode__DOT__inst_type;
    CData/*0:0*/ __VstlDidInit;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __VactDidInit;
    CData/*0:0*/ __VactContinue;
    VL_OUT(pc,31,0);
    VL_OUT(inst,31,0);
    VL_OUT(x10,31,0);
    VL_OUT(rdata1,31,0);
    VL_OUT(rdata2,31,0);
    VL_OUT(imm,31,0);
    IData/*31:0*/ top__DOT__dnpc;
    IData/*31:0*/ top__DOT__mem_wdata;
    IData/*31:0*/ top__DOT__gpr_wdata;
    IData/*31:0*/ top__DOT__mem_waddr;
    IData/*31:0*/ top__DOT__mem_raddr;
    IData/*31:0*/ top__DOT__ram__DOT__inst_temp;
    IData/*31:0*/ top__DOT__ram__DOT__rdata_temp;
    IData/*31:0*/ top__DOT__inst_execute__DOT__unnamedblk1__DOT__snpc;
    IData/*31:0*/ top__DOT__inst_execute__DOT__unnamedblk1__DOT__alu_res;
    IData/*31:0*/ __Vtask_top__DOT__ram__DOT__pmem_read__0__rdata;
    IData/*31:0*/ __Vtask_top__DOT__ram__DOT__pmem_read__1__rdata;
    IData/*31:0*/ __Vtrigrprev__TOP__top__DOT__ram__DOT__rdata_temp;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<IData/*31:0*/, 32> top__DOT__gpr__DOT__x;
    VlTriggerVec<2> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
