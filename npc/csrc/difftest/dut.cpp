#include <dlfcn.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "../utils.h"
#include "../../include/generated/autoconf.h"



struct NPC_State {
	uint32_t gpr[32];
	uint32_t pc;
};

extern uint32_t *cpu_gpr;




void (*ref_difftest_memcpy)(uint32_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
void (*ref_difftest_init)(int port) = NULL;


void init_difftest(char *ref_so_file, long img_size, void *img) {

	printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
  assert(ref_so_file != NULL);
	void *handle;
  handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);

	ref_difftest_memcpy = (void (*)(uint32_t, void *, size_t, bool))dlsym(handle, "difftest_memcpy");
    ref_difftest_regcpy = (void (*)(void *, bool))dlsym(handle, "difftest_regcpy");
    ref_difftest_exec   = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
    ref_difftest_init   = (void (*)(int))dlsym(handle, "difftest_init");

    assert(ref_difftest_memcpy && ref_difftest_regcpy && ref_difftest_exec && ref_difftest_init);

  // Log("Differential testing: %s", ANSI_FMT("ON", ANSI_FG_GREEN));
  // Log("The result of every instruction will be compared with %s. "
  //     "This will help you a lot for debugging, but also significantly reduce the performance. "
  //     "If it is not necessary, you can turn it off in menuconfig.", ref_so_file);


    ref_difftest_init(1234);

	NPC_State init_state = {0};
	init_state.pc = 0x80000000; // 初始 PC

  ref_difftest_memcpy(0x80000000, img, img_size, true); // DIFFTEST_TO_REF 是 true

}


bool isa_difftest_checkregs(NPC_State *ref, uint32_t pc) {
    // 1. 检查 PC
    if (ref->pc != pc) {
        printf("\n[Difftest] PC Mismatch!\n");
        printf("Expected (NEMU): 0x%08x\n", ref->pc);
        printf("Actual   (NPC) : 0x%08x\n", pc);
        return false;
    }
    // }else {
	// 			printf("[Difftest] PC Match: 0x%08x\n", pc);
	// 	}

    // 2. 检查 32 个通用寄存器
    for (int i = 0; i < 32; i++) {
        if (ref->gpr[i] != cpu_gpr[i]) {
            printf("\n[Difftest] GPR[%d] Mismatch!\n", i);
            printf("Expected (NEMU): 0x%08x\n", ref->gpr[i]);
            printf("Actual   (NPC) : 0x%08x\n", cpu_gpr[i]);
            return false;
        }
    //     }else {
	// 			printf("/[Difftest_GPR] DUT[%d]: 0x%08x VS REF[%d]:0x%08x\n", i, cpu_gpr[i], i, ref->gpr[i]);
    // }
	}
	 return true;
}



static bool is_skip_ref = false;
void difftest_skip_ref() {
  is_skip_ref = true;
}

void difftest_step(uint32_t npc_pc, void *npc_regs) {
     //printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");

    if (is_skip_ref) {
        if (ref_difftest_regcpy) {
            NPC_State dut_r;
            dut_r.pc = npc_pc;
            for (int i = 0; i < 32; i++) {
                dut_r.gpr[i] = cpu_gpr[i];
            }
            ref_difftest_regcpy(&dut_r, true);
        }
        is_skip_ref = false;
        return;
    }

    NPC_State ref_r; 

    // 1. 让裁判（NEMU）执行一步
    if (ref_difftest_exec) {
        ref_difftest_exec(1);
    }

    // 2. 将裁判执行后的状态拷贝到 ref_r 结构体中
    // 这里的 false 表示从 Reference (NEMU) 拷贝到 DUT (NPC)
    if (ref_difftest_regcpy) {
        ref_difftest_regcpy(&ref_r, false); 
    }

    // 3. 调用比对函数
    // 此时 &ref_r 的类型是 NPC_State*，完美匹配函数参数
    if (!isa_difftest_checkregs(&ref_r, npc_pc)) {
        printf("Difftest failed at PC = 0x%08x\n", npc_pc);
        assert(0);
    }
}


