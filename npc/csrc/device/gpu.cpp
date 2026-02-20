#include <SDL2/SDL.h>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <sys/time.h>

#define SCREEN_W 400
#define SCREEN_H 300

// 地址定义（必须与 AM 端的实现严格一致）
#define VGACTL_ADDR 0xa0000100
#define FB_ADDR     0xa1000000
#define SYNC_ADDR   (VGACTL_ADDR + 4)

static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static uint32_t *vmem = NULL;
static bool vga_init_done = false;

void init_vga() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return;
    SDL_Window *window = SDL_CreateWindow("NPC-VGA", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_W * 2, SCREEN_H * 2, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);
    vmem = (uint32_t *)malloc(SCREEN_W * SCREEN_H * sizeof(uint32_t));
    memset(vmem, 0, SCREEN_W * SCREEN_H * sizeof(uint32_t));
    vga_init_done = true;
}

void update_screen() {
    if (!vga_init_done) return;

    SDL_UpdateTexture(texture, NULL, vmem, SCREEN_W * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Event event;
    while (SDL_PollEvent(&event));
}

// 供 pmem_read 调用的拦截接口
bool gpu_read(uint32_t addr, uint32_t *data) {
    if (addr == VGACTL_ADDR) {
        *data = (SCREEN_W << 16) | SCREEN_H;
        return true;
    }
    if (addr >= FB_ADDR && addr < FB_ADDR + (SCREEN_W * SCREEN_H * 4)) {
        uint32_t offset = (addr - FB_ADDR) / 4;
        *data = vmem[offset];
        return true;
    }
    return false;
}

// 供 pmem_write 调用的拦截接口
bool gpu_write(uint32_t addr, uint32_t data, uint8_t wmask) {
    // 拦截显存写入
    if (addr >= FB_ADDR && addr < FB_ADDR + (SCREEN_W * SCREEN_H * 4)) {
        if (!vga_init_done) init_vga();
        uint32_t offset = (addr - FB_ADDR) / 4;
        
        // 处理掩码写入
        uint32_t mask = 0;
        if (wmask & 0x01) mask |= 0x000000FF;
        if (wmask & 0x02) mask |= 0x0000FF00;
        if (wmask & 0x04) mask |= 0x00FF0000;
        if (wmask & 0x08) mask |= 0xFF000000;
        vmem[offset] = (vmem[offset] & ~mask) | (data & mask);
        return true;
    }
    
    // 拦截同步触发
    if (addr == SYNC_ADDR) {
        if (data & 0x1) update_screen();
        return true;
    }
    
    return false;
}