// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigrprev__TOP__top__DOT__ram__DOT__rdata_temp 
        = vlSelf->top__DOT__ram__DOT__rdata_temp;
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
}

void Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(const IData/*31:0*/ &a);

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    Vtop___024root____Vdpiimwrap_top__DOT__gpr__DOT__set_gpr_ptr__Vdpioc2_TOP(
                                                                              vlSelf->top__DOT__gpr__DOT__x
                                                                              [0U]);
    VL_WRITEF("Verilog side: GPR pointer sent to C.\n");
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vtop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 1, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vtop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
    if (vlSelf->__VstlTriggered.at(1U)) {
        VL_DBG_MSGF("         'stl' region trigger index 1 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
}
#endif  // VL_DEBUG

void Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(IData/*31:0*/ raddr, IData/*31:0*/ &rdata, CData/*7:0*/ rmask);
void Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__invalid_inst_trap_TOP(IData/*31:0*/ pc, IData/*31:0*/ inst);
void Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__ebreak_TOP();

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->x10 = vlSelf->top__DOT__gpr__DOT__x[0xaU];
    Vtop___024root____Vdpiimwrap_top__DOT__ram__DOT__pmem_read_TOP(vlSelf->pc, vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata, 0xfU);
    vlSelf->top__DOT__ram__DOT__inst_temp = vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata;
    vlSelf->inst = vlSelf->top__DOT__ram__DOT__inst_temp;
    vlSelf->top__DOT__gpr_wen = 0U;
    vlSelf->top__DOT__mem_wen = 0U;
    if ((1U & (~ ((((((((0x100073U == vlSelf->inst) 
                        | (0x13U == (0x707fU & vlSelf->inst))) 
                       | (0x4013U == (0x707fU & vlSelf->inst))) 
                      | (0x67U == (0x7fU & vlSelf->inst))) 
                     | (0x5013U == (0xfe00707fU & vlSelf->inst))) 
                    | (0x1013U == (0xfe00707fU & vlSelf->inst))) 
                   | (0x2003U == (0x707fU & vlSelf->inst))) 
                  | (3U == (0x707fU & vlSelf->inst)))))) {
        if ((1U & (~ ((((((((0x5003U == (0x707fU & vlSelf->inst)) 
                            | (0x4003U == (0x707fU 
                                           & vlSelf->inst))) 
                           | (0x1003U == (0x707fU & vlSelf->inst))) 
                          | (0x3013U == (0x707fU & vlSelf->inst))) 
                         | (0x2013U == (0x707fU & vlSelf->inst))) 
                        | (0x40005013U == (0xfe00707fU 
                                           & vlSelf->inst))) 
                       | (0x7013U == (0x707fU & vlSelf->inst))) 
                      | (0x6013U == (0x707fU & vlSelf->inst)))))) {
            if ((1U & (~ ((((((((0x1033U == (0xfe00707fU 
                                             & vlSelf->inst)) 
                                | (0x33U == (0xfe00707fU 
                                             & vlSelf->inst))) 
                               | (0x40000033U == (0xfe00707fU 
                                                  & vlSelf->inst))) 
                              | (0x3033U == (0xfe00707fU 
                                             & vlSelf->inst))) 
                             | (0x2033U == (0xfe00707fU 
                                            & vlSelf->inst))) 
                            | (0x40005033U == (0xfe00707fU 
                                               & vlSelf->inst))) 
                           | (0x5033U == (0xfe00707fU 
                                          & vlSelf->inst))) 
                          | (0x4033U == (0xfe00707fU 
                                         & vlSelf->inst)))))) {
                if (((((((((0x6033U == (0xfe00707fU 
                                        & vlSelf->inst)) 
                           | (0x7033U == (0xfe00707fU 
                                          & vlSelf->inst))) 
                          | (0x17U == (0x7fU & vlSelf->inst))) 
                         | (0x37U == (0x7fU & vlSelf->inst))) 
                        | (0x6fU == (0x7fU & vlSelf->inst))) 
                       | (0x2023U == (0x707fU & vlSelf->inst))) 
                      | (0x1023U == (0x707fU & vlSelf->inst))) 
                     | (0x23U == (0x707fU & vlSelf->inst)))) {
                    if ((0x6033U != (0xfe00707fU & vlSelf->inst))) {
                        if ((0x7033U != (0xfe00707fU 
                                         & vlSelf->inst))) {
                            if ((0x17U != (0x7fU & vlSelf->inst))) {
                                if ((0x37U != (0x7fU 
                                               & vlSelf->inst))) {
                                    if ((0x6fU != (0x7fU 
                                                   & vlSelf->inst))) {
                                        vlSelf->top__DOT__mem_wen = 1U;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelf->top__DOT__inst_valid = (((((((((0x100073U 
                                            == vlSelf->inst) 
                                           | (0x13U 
                                              == (0x707fU 
                                                  & vlSelf->inst))) 
                                          | (0x4013U 
                                             == (0x707fU 
                                                 & vlSelf->inst))) 
                                         | (0x67U == 
                                            (0x7fU 
                                             & vlSelf->inst))) 
                                        | (0x5013U 
                                           == (0xfe00707fU 
                                               & vlSelf->inst))) 
                                       | (0x1013U == 
                                          (0xfe00707fU 
                                           & vlSelf->inst))) 
                                      | (0x2003U == 
                                         (0x707fU & vlSelf->inst))) 
                                     | (3U == (0x707fU 
                                               & vlSelf->inst))) 
                                    | (((((((((0x5003U 
                                               == (0x707fU 
                                                   & vlSelf->inst)) 
                                              | (0x4003U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->inst))) 
                                             | (0x1003U 
                                                == 
                                                (0x707fU 
                                                 & vlSelf->inst))) 
                                            | (0x3013U 
                                               == (0x707fU 
                                                   & vlSelf->inst))) 
                                           | (0x2013U 
                                              == (0x707fU 
                                                  & vlSelf->inst))) 
                                          | (0x40005013U 
                                             == (0xfe00707fU 
                                                 & vlSelf->inst))) 
                                         | (0x7013U 
                                            == (0x707fU 
                                                & vlSelf->inst))) 
                                        | (0x6013U 
                                           == (0x707fU 
                                               & vlSelf->inst))) 
                                       | (((((((((0x1033U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelf->inst)) 
                                                 | (0x33U 
                                                    == 
                                                    (0xfe00707fU 
                                                     & vlSelf->inst))) 
                                                | (0x40000033U 
                                                   == 
                                                   (0xfe00707fU 
                                                    & vlSelf->inst))) 
                                               | (0x3033U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelf->inst))) 
                                              | (0x2033U 
                                                 == 
                                                 (0xfe00707fU 
                                                  & vlSelf->inst))) 
                                             | (0x40005033U 
                                                == 
                                                (0xfe00707fU 
                                                 & vlSelf->inst))) 
                                            | (0x5033U 
                                               == (0xfe00707fU 
                                                   & vlSelf->inst))) 
                                           | (0x4033U 
                                              == (0xfe00707fU 
                                                  & vlSelf->inst))) 
                                          | (((((((((0x6033U 
                                                     == 
                                                     (0xfe00707fU 
                                                      & vlSelf->inst)) 
                                                    | (0x7033U 
                                                       == 
                                                       (0xfe00707fU 
                                                        & vlSelf->inst))) 
                                                   | (0x17U 
                                                      == 
                                                      (0x7fU 
                                                       & vlSelf->inst))) 
                                                  | (0x37U 
                                                     == 
                                                     (0x7fU 
                                                      & vlSelf->inst))) 
                                                 | (0x6fU 
                                                    == 
                                                    (0x7fU 
                                                     & vlSelf->inst))) 
                                                | (0x2023U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->inst))) 
                                               | (0x1023U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelf->inst))) 
                                              | (0x23U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->inst))) 
                                             | ((0x63U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->inst)) 
                                                | ((0x1063U 
                                                    == 
                                                    (0x707fU 
                                                     & vlSelf->inst)) 
                                                   | ((0x5063U 
                                                       == 
                                                       (0x707fU 
                                                        & vlSelf->inst)) 
                                                      | ((0x7063U 
                                                          == 
                                                          (0x707fU 
                                                           & vlSelf->inst)) 
                                                         | ((0x4063U 
                                                             == 
                                                             (0x707fU 
                                                              & vlSelf->inst)) 
                                                            | (0x6063U 
                                                               == 
                                                               (0x707fU 
                                                                & vlSelf->inst)))))))))));
    vlSelf->top__DOT__mem_ren = 0U;
    vlSelf->top__DOT__opcode = 0U;
    vlSelf->top__DOT__func3 = 0U;
    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
    if (((((((((0x100073U == vlSelf->inst) | (0x13U 
                                              == (0x707fU 
                                                  & vlSelf->inst))) 
              | (0x4013U == (0x707fU & vlSelf->inst))) 
             | (0x67U == (0x7fU & vlSelf->inst))) | 
            (0x5013U == (0xfe00707fU & vlSelf->inst))) 
           | (0x1013U == (0xfe00707fU & vlSelf->inst))) 
          | (0x2003U == (0x707fU & vlSelf->inst))) 
         | (3U == (0x707fU & vlSelf->inst)))) {
        if ((0x100073U != vlSelf->inst)) {
            vlSelf->top__DOT__gpr_wen = 1U;
            if ((0x13U != (0x707fU & vlSelf->inst))) {
                if ((0x4013U != (0x707fU & vlSelf->inst))) {
                    if ((0x67U != (0x7fU & vlSelf->inst))) {
                        if ((0x5013U != (0xfe00707fU 
                                         & vlSelf->inst))) {
                            if ((0x1013U != (0xfe00707fU 
                                             & vlSelf->inst))) {
                                vlSelf->top__DOT__mem_ren = 1U;
                            }
                        }
                    }
                }
            }
        } else {
            vlSelf->top__DOT__gpr_wen = 0U;
        }
        if ((0x100073U == vlSelf->inst)) {
            vlSelf->top__DOT__opcode = 0x73U;
            vlSelf->top__DOT__func3 = 0U;
        } else if ((0x13U == (0x707fU & vlSelf->inst))) {
            vlSelf->top__DOT__opcode = 0x13U;
            vlSelf->top__DOT__func3 = 0U;
        } else if ((0x4013U == (0x707fU & vlSelf->inst))) {
            vlSelf->top__DOT__opcode = 0x13U;
            vlSelf->top__DOT__func3 = 4U;
        } else if ((0x67U == (0x7fU & vlSelf->inst))) {
            vlSelf->top__DOT__opcode = 0x67U;
            vlSelf->top__DOT__func3 = 0U;
        } else if ((0x5013U == (0xfe00707fU & vlSelf->inst))) {
            vlSelf->top__DOT__opcode = 0x13U;
            vlSelf->top__DOT__func3 = 5U;
        } else if ((0x1013U == (0xfe00707fU & vlSelf->inst))) {
            vlSelf->top__DOT__opcode = 0x13U;
            vlSelf->top__DOT__func3 = 1U;
        } else {
            vlSelf->top__DOT__opcode = 3U;
            vlSelf->top__DOT__func3 = ((0x2003U == 
                                        (0x707fU & vlSelf->inst))
                                        ? 2U : 0U);
        }
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
    } else if (((((((((0x5003U == (0x707fU & vlSelf->inst)) 
                      | (0x4003U == (0x707fU & vlSelf->inst))) 
                     | (0x1003U == (0x707fU & vlSelf->inst))) 
                    | (0x3013U == (0x707fU & vlSelf->inst))) 
                   | (0x2013U == (0x707fU & vlSelf->inst))) 
                  | (0x40005013U == (0xfe00707fU & vlSelf->inst))) 
                 | (0x7013U == (0x707fU & vlSelf->inst))) 
                | (0x6013U == (0x707fU & vlSelf->inst)))) {
        vlSelf->top__DOT__gpr_wen = 1U;
        if ((0x5003U == (0x707fU & vlSelf->inst))) {
            vlSelf->top__DOT__mem_ren = 1U;
            vlSelf->top__DOT__opcode = 3U;
            vlSelf->top__DOT__func3 = 5U;
        } else if ((0x4003U == (0x707fU & vlSelf->inst))) {
            vlSelf->top__DOT__mem_ren = 1U;
            vlSelf->top__DOT__opcode = 3U;
            vlSelf->top__DOT__func3 = 4U;
        } else if ((0x1003U == (0x707fU & vlSelf->inst))) {
            vlSelf->top__DOT__mem_ren = 1U;
            vlSelf->top__DOT__opcode = 3U;
            vlSelf->top__DOT__func3 = 1U;
        } else {
            vlSelf->top__DOT__opcode = 0x13U;
            vlSelf->top__DOT__func3 = ((0x3013U == 
                                        (0x707fU & vlSelf->inst))
                                        ? 3U : ((0x2013U 
                                                 == 
                                                 (0x707fU 
                                                  & vlSelf->inst))
                                                 ? 2U
                                                 : 
                                                ((0x40005013U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelf->inst))
                                                  ? 5U
                                                  : 
                                                 ((0x7013U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelf->inst))
                                                   ? 7U
                                                   : 6U))));
        }
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 0U;
    } else if (((((((((0x1033U == (0xfe00707fU & vlSelf->inst)) 
                      | (0x33U == (0xfe00707fU & vlSelf->inst))) 
                     | (0x40000033U == (0xfe00707fU 
                                        & vlSelf->inst))) 
                    | (0x3033U == (0xfe00707fU & vlSelf->inst))) 
                   | (0x2033U == (0xfe00707fU & vlSelf->inst))) 
                  | (0x40005033U == (0xfe00707fU & vlSelf->inst))) 
                 | (0x5033U == (0xfe00707fU & vlSelf->inst))) 
                | (0x4033U == (0xfe00707fU & vlSelf->inst)))) {
        vlSelf->top__DOT__gpr_wen = 1U;
        vlSelf->top__DOT__opcode = 0x33U;
        vlSelf->top__DOT__func3 = ((0x1033U == (0xfe00707fU 
                                                & vlSelf->inst))
                                    ? 1U : ((0x33U 
                                             == (0xfe00707fU 
                                                 & vlSelf->inst))
                                             ? 0U : 
                                            ((0x40000033U 
                                              == (0xfe00707fU 
                                                  & vlSelf->inst))
                                              ? 0U : 
                                             ((0x3033U 
                                               == (0xfe00707fU 
                                                   & vlSelf->inst))
                                               ? 3U
                                               : ((0x2033U 
                                                   == 
                                                   (0xfe00707fU 
                                                    & vlSelf->inst))
                                                   ? 2U
                                                   : 
                                                  ((0x40005033U 
                                                    == 
                                                    (0xfe00707fU 
                                                     & vlSelf->inst))
                                                    ? 5U
                                                    : 
                                                   ((0x5033U 
                                                     == 
                                                     (0xfe00707fU 
                                                      & vlSelf->inst))
                                                     ? 5U
                                                     : 4U)))))));
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 1U;
    } else if (((((((((0x6033U == (0xfe00707fU & vlSelf->inst)) 
                      | (0x7033U == (0xfe00707fU & vlSelf->inst))) 
                     | (0x17U == (0x7fU & vlSelf->inst))) 
                    | (0x37U == (0x7fU & vlSelf->inst))) 
                   | (0x6fU == (0x7fU & vlSelf->inst))) 
                  | (0x2023U == (0x707fU & vlSelf->inst))) 
                 | (0x1023U == (0x707fU & vlSelf->inst))) 
                | (0x23U == (0x707fU & vlSelf->inst)))) {
        if ((0x6033U == (0xfe00707fU & vlSelf->inst))) {
            vlSelf->top__DOT__gpr_wen = 1U;
            vlSelf->top__DOT__opcode = 0x33U;
            vlSelf->top__DOT__func3 = 6U;
            vlSelf->top__DOT__inst_decode__DOT__inst_type = 1U;
        } else if ((0x7033U == (0xfe00707fU & vlSelf->inst))) {
            vlSelf->top__DOT__gpr_wen = 1U;
            vlSelf->top__DOT__opcode = 0x33U;
            vlSelf->top__DOT__func3 = 7U;
            vlSelf->top__DOT__inst_decode__DOT__inst_type = 1U;
        } else {
            if ((0x17U == (0x7fU & vlSelf->inst))) {
                vlSelf->top__DOT__gpr_wen = 1U;
                vlSelf->top__DOT__opcode = 0x17U;
                vlSelf->top__DOT__inst_decode__DOT__inst_type = 2U;
            } else if ((0x37U == (0x7fU & vlSelf->inst))) {
                vlSelf->top__DOT__gpr_wen = 1U;
                vlSelf->top__DOT__opcode = 0x37U;
                vlSelf->top__DOT__inst_decode__DOT__inst_type = 2U;
            } else if ((0x6fU == (0x7fU & vlSelf->inst))) {
                vlSelf->top__DOT__gpr_wen = 1U;
                vlSelf->top__DOT__opcode = 0x6fU;
                vlSelf->top__DOT__inst_decode__DOT__inst_type = 4U;
            } else {
                vlSelf->top__DOT__opcode = 0x23U;
                vlSelf->top__DOT__inst_decode__DOT__inst_type = 5U;
            }
            if ((0x17U != (0x7fU & vlSelf->inst))) {
                if ((0x37U != (0x7fU & vlSelf->inst))) {
                    if ((0x6fU != (0x7fU & vlSelf->inst))) {
                        vlSelf->top__DOT__func3 = (
                                                   (0x2023U 
                                                    == 
                                                    (0x707fU 
                                                     & vlSelf->inst))
                                                    ? 2U
                                                    : 
                                                   ((0x1023U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelf->inst))
                                                     ? 1U
                                                     : 0U));
                    }
                }
            }
        }
    } else if ((0x63U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 0U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    } else if ((0x1063U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 1U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    } else if ((0x5063U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 5U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    } else if ((0x7063U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 7U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    } else if ((0x4063U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 4U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    } else if ((0x6063U == (0x707fU & vlSelf->inst))) {
        vlSelf->top__DOT__opcode = 0x63U;
        vlSelf->top__DOT__func3 = 6U;
        vlSelf->top__DOT__inst_decode__DOT__inst_type = 6U;
    }
    vlSelf->imm = 0U;
    vlSelf->top__DOT__raddr1 = 0U;
    vlSelf->top__DOT__raddr2 = 0U;
    vlSelf->top__DOT__gpr_waddr = 0U;
    if ((4U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        if ((2U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
                vlSelf->imm = 0U;
                vlSelf->top__DOT__raddr1 = 0U;
                vlSelf->top__DOT__gpr_waddr = 0U;
            } else {
                vlSelf->imm = (((- (IData)((vlSelf->inst 
                                            >> 0x1fU))) 
                                << 0xcU) | ((0x800U 
                                             & (vlSelf->inst 
                                                << 4U)) 
                                            | ((0x7e0U 
                                                & (vlSelf->inst 
                                                   >> 0x14U)) 
                                               | (0x1eU 
                                                  & (vlSelf->inst 
                                                     >> 7U)))));
                vlSelf->top__DOT__raddr1 = (0x1fU & 
                                            (vlSelf->inst 
                                             >> 0xfU));
                vlSelf->top__DOT__raddr2 = (0x1fU & 
                                            (vlSelf->inst 
                                             >> 0x14U));
            }
        } else if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            vlSelf->imm = (((- (IData)((vlSelf->inst 
                                        >> 0x1fU))) 
                            << 0xcU) | ((0xfe0U & (vlSelf->inst 
                                                   >> 0x14U)) 
                                        | (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U))));
            vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                                 >> 0xfU));
            vlSelf->top__DOT__raddr2 = (0x1fU & (vlSelf->inst 
                                                 >> 0x14U));
        } else {
            vlSelf->imm = (((- (IData)((vlSelf->inst 
                                        >> 0x1fU))) 
                            << 0x14U) | ((0xff000U 
                                          & vlSelf->inst) 
                                         | ((0x800U 
                                             & (vlSelf->inst 
                                                >> 9U)) 
                                            | (0x7feU 
                                               & (vlSelf->inst 
                                                  >> 0x14U)))));
            vlSelf->top__DOT__gpr_waddr = (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U));
        }
    } else if ((2U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
            vlSelf->imm = 0U;
            vlSelf->top__DOT__raddr1 = 0U;
            vlSelf->top__DOT__gpr_waddr = 0U;
        } else {
            vlSelf->imm = (0xfffff000U & vlSelf->inst);
            vlSelf->top__DOT__gpr_waddr = (0x1fU & 
                                           (vlSelf->inst 
                                            >> 7U));
        }
    } else if ((1U & (IData)(vlSelf->top__DOT__inst_decode__DOT__inst_type))) {
        vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                             >> 0xfU));
        vlSelf->top__DOT__raddr2 = (0x1fU & (vlSelf->inst 
                                             >> 0x14U));
        vlSelf->top__DOT__gpr_waddr = (0x1fU & (vlSelf->inst 
                                                >> 7U));
    } else {
        vlSelf->imm = (((- (IData)((vlSelf->inst >> 0x1fU))) 
                        << 0xcU) | (vlSelf->inst >> 0x14U));
        vlSelf->top__DOT__raddr1 = (0x1fU & (vlSelf->inst 
                                             >> 0xfU));
        vlSelf->top__DOT__gpr_waddr = (0x1fU & (vlSelf->inst 
                                                >> 7U));
    }
    if ((1U & (~ ((IData)(vlSelf->rst) | (IData)(vlSelf->top__DOT__inst_valid))))) {
        Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__invalid_inst_trap_TOP(vlSelf->pc, vlSelf->inst);
    }
    if ((((0x73U == (IData)(vlSelf->top__DOT__opcode)) 
          & (0U == (IData)(vlSelf->top__DOT__func3))) 
         & (vlSelf->inst >> 0x14U))) {
        Vtop___024root____Vdpiimwrap_top__DOT__inst_execute__DOT__ebreak_TOP();
    }
    vlSelf->rdata1 = ((0U == (IData)(vlSelf->top__DOT__raddr1))
                       ? 0U : vlSelf->top__DOT__gpr__DOT__x
                      [vlSelf->top__DOT__raddr1]);
    vlSelf->rdata2 = ((0U == (IData)(vlSelf->top__DOT__raddr2))
                       ? 0U : vlSelf->top__DOT__gpr__DOT__x
                      [vlSelf->top__DOT__raddr2]);
}

void Vtop___024root___act_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
    if ((vlSelf->__VstlTriggered.at(0U) | vlSelf->__VstlTriggered.at(1U))) {
        Vtop___024root___act_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
    if (vlSelf->__VactTriggered.at(1U)) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @([hybrid] top.ram.rdata_temp)\n");
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst = 0;
    vlSelf->pc = 0;
    vlSelf->inst = 0;
    vlSelf->x10 = 0;
    vlSelf->rdata1 = 0;
    vlSelf->rdata2 = 0;
    vlSelf->imm = 0;
    vlSelf->top__DOT__dnpc = 0;
    vlSelf->top__DOT__mem_wdata = 0;
    vlSelf->top__DOT__wmask = 0;
    vlSelf->top__DOT__rmask = 0;
    vlSelf->top__DOT__gpr_wdata = 0;
    vlSelf->top__DOT__mem_waddr = 0;
    vlSelf->top__DOT__mem_raddr = 0;
    vlSelf->top__DOT__gpr_wen = 0;
    vlSelf->top__DOT__mem_wen = 0;
    vlSelf->top__DOT__mem_ren = 0;
    vlSelf->top__DOT__raddr1 = 0;
    vlSelf->top__DOT__raddr2 = 0;
    vlSelf->top__DOT__inst_valid = 0;
    vlSelf->top__DOT__opcode = 0;
    vlSelf->top__DOT__func3 = 0;
    vlSelf->top__DOT__gpr_waddr = 0;
    vlSelf->top__DOT__ram__DOT__inst_temp = 0;
    vlSelf->top__DOT__ram__DOT__rdata_temp = 0;
    vlSelf->top__DOT__inst_decode__DOT__inst_type = 0;
    vlSelf->top__DOT__inst_execute__DOT__unnamedblk1__DOT__snpc = 0;
    vlSelf->top__DOT__inst_execute__DOT__unnamedblk1__DOT__alu_res = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__gpr__DOT__x[__Vi0] = 0;
    }
    vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__0__rdata = 0;
    vlSelf->__Vtask_top__DOT__ram__DOT__pmem_read__1__rdata = 0;
    vlSelf->__Vtrigrprev__TOP__top__DOT__ram__DOT__rdata_temp = 0;
    vlSelf->__VstlDidInit = 0;
    vlSelf->__Vtrigrprev__TOP__clk = 0;
    vlSelf->__VactDidInit = 0;
}
