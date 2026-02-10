#include <am.h>
#include "../riscv.h"
// #include <stdio.h>
//#include <klib.h>
#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {

  uint32_t scancode = inl(0xa0000060);
  
  // 2. 只要不是 0 就暴力打印，不管是什么键
  // if (scancode != 0) {
  //     // 用最稳的字符打印配合十六进制
  //     putch('K'); putch(':');
  //     printf("%x\n", scancode); 
  // }

  kbd->keydown = (scancode & 0x8000) ? true : false;
  kbd->keycode = scancode & ~0x8000;
}