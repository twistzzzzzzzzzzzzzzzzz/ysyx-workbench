#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include "Vtop.h"
#include "verilated.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "verilated_dpi.h"
#define KEY_QUEUE_LEN 1024
extern Vtop* top_ptr;
// 模拟一个键盘内部的队列或寄存器
static uint32_t key_queue[KEY_QUEUE_LEN]; 
static int head = 0, tail = 0;


extern "C" uint32_t keyboard_read() {
    uint32_t k = 0;
    if (head != tail) {
        k = key_queue[head];
        head = (head + 1) % KEY_QUEUE_LEN;
          printf("a5 = 0x%08x\n", top_ptr->x15);
         printf("C++ side: read keycode 0x%08x from queue\n", k);
    }
    return k;
}




// 这个函数需要你在 main 循环中调用，用来同步 SDL 事件
static uint32_t translate_sdl_to_am(SDL_Keycode sym) {
    switch (sym) {
        // 第一排：功能键
        case SDLK_ESCAPE:    return 1;
        case SDLK_F1:        return 2;
        case SDLK_F2:        return 3;
        case SDLK_F3:        return 4;
        case SDLK_F4:        return 5;
        case SDLK_F5:        return 6;
        case SDLK_F6:        return 7;
        case SDLK_F7:        return 8;
        case SDLK_F8:        return 9;
        case SDLK_F9:        return 10;
        case SDLK_F10:       return 11;
        case SDLK_F11:       return 12;
        case SDLK_F12:       return 13;

        // 第二排：数字键
        case SDLK_BACKQUOTE: return 14;
        case SDLK_1:         return 15;
        case SDLK_2:         return 16;
        case SDLK_3:         return 17;
        case SDLK_4:         return 18;
        case SDLK_5:         return 19;
        case SDLK_6:         return 20;
        case SDLK_7:         return 21;
        case SDLK_8:         return 22;
        case SDLK_9:         return 23;
        case SDLK_0:         return 24;
        case SDLK_MINUS:     return 25;
        case SDLK_EQUALS:    return 26;
        case SDLK_BACKSPACE: return 27;

        // 第三排：QWERTY
        case SDLK_TAB:       return 28;
        case SDLK_q:         return 29;
        case SDLK_w:         return 30;
        case SDLK_e:         return 31;
        case SDLK_r:         return 32;
        case SDLK_t:         return 33;
        case SDLK_y:         return 34;
        case SDLK_u:         return 35;
        case SDLK_i:         return 36;
        case SDLK_o:         return 37;
        case SDLK_p:         return 38;
        case SDLK_LEFTBRACKET:  return 39;
        case SDLK_RIGHTBRACKET: return 40;
        case SDLK_BACKSLASH:    return 41;

        // 第四排：ASDFG
        case SDLK_CAPSLOCK:  return 42;
        case SDLK_a:         return 43;
        case SDLK_s:         return 44;
        case SDLK_d:         return 45;
        case SDLK_f:         return 46;
        case SDLK_g:         return 47;
        case SDLK_h:         return 48;
        case SDLK_j:         return 49;
        case SDLK_k:         return 50;
        case SDLK_l:         return 51;
        case SDLK_SEMICOLON: return 52;
        case SDLK_QUOTE:     return 53;
        case SDLK_RETURN:    return 54;

        // 第五排：ZXCVB
        case SDLK_LSHIFT:    return 55;
        case SDLK_z:         return 56;
        case SDLK_x:         return 57;
        case SDLK_c:         return 58;
        case SDLK_v:         return 59;
        case SDLK_b:         return 60;
        case SDLK_n:         return 61;
        case SDLK_m:         return 62;
        case SDLK_COMMA:     return 63;
        case SDLK_PERIOD:    return 64;
        case SDLK_SLASH:     return 65;
        case SDLK_RSHIFT:    return 66;

        // 第六排：控制键
        case SDLK_LCTRL:     return 67;
        case SDLK_APPLICATION: return 68;
        case SDLK_LALT:      return 69;
        case SDLK_SPACE:     return 70;
        case SDLK_RALT:      return 71;
        case SDLK_RCTRL:     return 72;

        // 方向键与功能块
        case SDLK_UP:        return 73;
        case SDLK_DOWN:      return 74;
        case SDLK_LEFT:      return 75;
        case SDLK_RIGHT:     return 76;
        case SDLK_INSERT:    return 77;
        case SDLK_DELETE:    return 78;
        case SDLK_HOME:      return 79;
        case SDLK_END:       return 80;
        case SDLK_PAGEUP:    return 81;
        case SDLK_PAGEDOWN:  return 82;

        default:             return 0;
    }
}
void update_keyboard_state() {
    SDL_Event event;
    // 使用 PollEvent 不会阻塞程序运行
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: 
                exit(0); 
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                uint32_t k = translate_sdl_to_am(event.key.keysym.sym);
                // printf("SDL event: sym=%d, am_code=%d\n", event.key.keysym.sym, k); 
                if (k != 0) {
                    // 按下为 0x8000 | keycode，抬起为 0 | keycode
                    uint32_t val = k | (event.type == SDL_KEYDOWN ? 0x8000 : 0);
                    key_queue[tail] = val;
                    tail = (tail + 1) % KEY_QUEUE_LEN;
                }
                break;
            }
        }
    }
}