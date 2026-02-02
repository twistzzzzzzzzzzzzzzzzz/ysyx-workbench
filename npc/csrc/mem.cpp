#include "Vtop.h"
#include "verilated.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "verilated_dpi.h"
#include <sys/time.h>




// 1. 定义内存
#define MEM_SIZE (64 * 1024 * 1024) // 64 MB
#define MEM_BASE 0x80000000
#define DEVICE_BASE 0xa0000000
#define RTC_ADDR (DEVICE_BASE + 0x00000048)
#define VGACTL_ADDR (DEVICE_BASE + 0x0000100)
#define SERIAL_PORT (0x10000000)
uint8_t pmem[MEM_SIZE];

extern Vtop* top_ptr;
extern uint32_t *cpu_gpr;
extern void difftest_skip_ref();


static uint64_t boot_time = 0;
static uint64_t get_time_internal() {
  struct timeval now;
  gettimeofday(&now, NULL);
  uint64_t us = now.tv_sec * 1000000 + now.tv_usec;
  if (boot_time == 0) boot_time = us;
  return us - boot_time;
}






extern "C" void set_gpr_ptr(const svOpenArrayHandle r) {
    // 使用 Verilator 提供的专用 API 提取真正的数组首地址
    // svGetArrayPtr 在某些版本中可用，但 datap() 是最稳妥的底层拿法
    cpu_gpr = (uint32_t *)(((VerilatedDpiOpenVar*)r)->datap());
    
    printf("C++ side: GPR pointer received at %p\n", r);
    printf("C++ side: GPR data actual address at %p\n", cpu_gpr);
}





// 在 mem.cpp 中
extern "C" uint32_t paddr_read(uint32_t addr, int len) {
    int data = 0;
    // 根据 len 生成对应的 rmask
    // len=1 -> 0x1, len=2 -> 0x3, len=4 -> 0xf
    char rmask = (len == 4) ? 0xf : (len == 2 ? 0x3 : 0x1);
    
    // 调用你给出的这个强大的函数
    pmem_read(addr, &data, rmask);
    
    return (uint32_t)data;
}


// 3. DPI-C 读内存 (供 Verilog 调用)
extern "C" void pmem_read(int raddr, int *rdata, char rmask) {
  
   if (raddr == RTC_ADDR || raddr == RTC_ADDR + 4) {
    difftest_skip_ref();
    uint64_t us = get_time_internal();
    if (raddr == RTC_ADDR) {
      *rdata = (uint32_t)us;
    } else {
      *rdata = (uint32_t)(us >> 32);
    }
    return;
  }

  if (raddr < MEM_BASE || raddr >= MEM_BASE + MEM_SIZE) {
      difftest_skip_ref();
      *rdata = 0;
      return;
  }

  // 计算偏移量
  uint32_t index = raddr - MEM_BASE;
  uint8_t *p = (uint8_t *)(pmem + index);
  
  // 根据 rmask 读取数据
  int data = 0;
  if (rmask & 0x01) { data |= (p[0]);       }
  if (rmask & 0x02) { data |= (p[1] << 8);  }
  if (rmask & 0x04) { data |= (p[2] << 16); }
  if (rmask & 0x08) { data |= (p[3] << 24); }
  *rdata = data;

}



// 4. DPI-C 写内存 (供 Verilog 调用)
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  if (waddr == SERIAL_PORT) {
      difftest_skip_ref();
      fputc((char)wdata, stdout); 
      fflush(stdout);
      return;
  }

  if (waddr < MEM_BASE || waddr >= MEM_BASE + MEM_SIZE) {
      difftest_skip_ref();
      return;
  }

  uint32_t index = waddr - MEM_BASE;
  uint8_t *p = (uint8_t *)(pmem + index);

 

  // 根据 wmask 逐字节写入
  // wmask 的第 0 位对应 wdata 的最低字节 (0-7位)
  // wmask 的第 1 位对应 wdata 的次低字节 (8-15位) ...
  if (wmask & 0x01) { p[0] = (wdata)       & 0xFF; }
  if (wmask & 0x02) { p[1] = (wdata >> 8)  & 0xFF; }
  if (wmask & 0x04) { p[2] = (wdata >> 16) & 0xFF; }
  if (wmask & 0x08) { p[3] = (wdata >> 24) & 0xFF; }
}






void isa_reg_display() {
    printf("DEBUG: cpu_gpr address is %p\n", cpu_gpr);
    if (cpu_gpr == NULL) {
        printf("ERROR: Bridge broken! The interaction layer cannot see the hardware registers.\n");
        return;
    }
  for (int i = 0; i < 32; i++) { // 必须是 < 32，不能是 <= 32
    if (cpu_gpr != NULL) {
      printf("x%-2d: 0x%08x\n", i, cpu_gpr[i]);
    } else {
      printf("Error: cpu_gpr is NULL!\n");
      return;
    }
  }
}