//verilator -Wall -I./vsrc ./vsrc/top.v ./csrc/top_main.cpp --cc --trace-fst --exe --build
#include "Vtop.h"
#include "verilated.h"
#include "verilated_fst_c.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    VerilatedFstC* tfp = new VerilatedFstC;

    Verilated::traceEverOn(true);
    top->trace(tfp, 99);
#ifdef TRACE_FST_PATH
        // 如果定义了 TRACE_FST_PATH，则将其字符串化用于打开文件
        #define STR_HELPER(x) #x
        #define STR(x) STR_HELPER(x)
        tfp->open(STR(TRACE_FST_PATH));
#else
        tfp->open("wave.fst");
#endif

    top->rst = 1;
    top->clk = 0;
    top->eval();
    tfp->dump(0);

    top->clk = 1;
    top->eval();
    tfp->dump(1);

    top->rst = 0;
    top->eval();
    tfp->dump(2);

    vluint64_t tick = 2; // 已经 dump 到 2
    while (!Verilated::gotFinish()) {
        top->clk = 0;
        top->eval();
        tfp->dump(++tick);

        top->clk = 1;
        top->eval();
        tfp->dump(++tick);
    }

    tfp->close();
    delete top;
    delete tfp;
    return 0;
}
