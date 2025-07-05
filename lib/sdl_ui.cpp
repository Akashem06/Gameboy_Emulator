#include "sdl_ui.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gameboy.hpp"
#include "log.hpp"

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_Surface *screen;

SDL_Window *sdlDebugWindow;
SDL_Renderer *sdlDebugRenderer;
SDL_Texture *sdlDebugTexture;
SDL_Surface *debugScreen;

static const uint32_t gameboy_palette[4] = {
  0xFFFFFFFF,  // White
  0xAAAAAAFF,  // Light Gray
  0x555555FF,  // Dark Gray
  0x000000FF   // Black
};

SDLUI::SDLUI() {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdlWindow, &sdlRenderer);

  screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32U, 0x00FF0000U, 0x0000FF00U, 0x000000FFU, 0xFF000000U);

  sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_CreateWindowAndRenderer(16 * 8 * scale, 32 * 8 * scale, 0, &sdlDebugWindow, &sdlDebugRenderer);

  debugScreen =
      SDL_CreateRGBSurface(0, (16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

  sdlDebugTexture = SDL_CreateTexture(sdlDebugRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, (16 * 8 * scale) + (16 * scale),
                                      (32 * 8 * scale) + (64 * scale));

  int x, y;
  SDL_GetWindowPosition(sdlWindow, &x, &y);
  SDL_SetWindowPosition(sdlDebugWindow, x + SCREEN_WIDTH + 10, y);
}

SDLUI::~SDLUI() {
  SDL_DestroyTexture(sdlTexture);
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
}

void SDLUI::handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        abort_event = true;
        break;
    }
  }
}

bool SDLUI::abortEvent() {
  return abort_event;
}

void SDLUI::renderFrame(Framebuffer &fb) {
  void *pixels;
  int pitch;
  SDL_LockTexture(sdlTexture, nullptr, &pixels, &pitch);

  uint32_t *dst = (uint32_t *)pixels;

  for (int y = 0; y < SCREEN_HEIGHT; ++y) {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
      uint8_t color_index = fb.get_pixel(x, y);
      dst[y * (pitch / 4) + x] = gameboy_palette[color_index];
    }
  }

  SDL_UnlockTexture(sdlTexture);

  SDL_RenderClear(sdlRenderer);
  SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
  SDL_RenderPresent(sdlRenderer);
}
