#include "verilated.h"
#include <cstdio>

extern "C" void npc_trap(int code) {
    std::printf("NPC hit ebreak, code = %d\n", code);
    Verilated::gotFinish(true);
}
