#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  // 1. 从键盘控制器地址读取 32 位扫描码
  uint32_t scancode = inl(KBD_ADDR);

  // 2. 解析按键状态：如果第 15 位是 1，则表示这是一个按下事件
  kbd->keydown = (scancode & KEYDOWN_MASK) ? true : false;

  // 3. 解析键码：去掉第 15 位的标志位，剩下的就是键码
  kbd->keycode = scancode & ~KEYDOWN_MASK;
}