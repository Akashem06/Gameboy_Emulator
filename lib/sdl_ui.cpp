#include "sdl_ui.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "gameboy.hpp"

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_Surface *screen;

SDL_Window *sdlDebugWindow;
SDL_Renderer *sdlDebugRenderer;
SDL_Texture *sdlDebugTexture;
SDL_Surface *debugScreen;

SDLUI::SDLUI() {
  SDL_Init(SDL_INIT_VIDEO);
  printf("SDL INIT\n");
  TTF_Init();
  printf("TTF INIT\n");

  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdlWindow, &sdlRenderer);

  screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32U, 0x00FF0000U, 0x0000FF00U,
                                0x000000FFU, 0xFF000000U);

  sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                 SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_CreateWindowAndRenderer(16 * 8 * scale, 32 * 8 * scale, 0, &sdlDebugWindow,
                              &sdlDebugRenderer);

  debugScreen =
      SDL_CreateRGBSurface(0, (16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale), 32,
                           0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

  sdlDebugTexture =
      SDL_CreateTexture(sdlDebugRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                        (16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale));

  int x, y;
  SDL_GetWindowPosition(sdlWindow, &x, &y);
  SDL_SetWindowPosition(sdlDebugWindow, x + SCREEN_WIDTH + 10, y);
}

SDLUI::~SDLUI() {
  SDL_DestroyTexture(sdlTexture);
  SDL_DestroyRenderer(sdlDebugRenderer);
  SDL_DestroyWindow(sdlDebugWindow);
  SDL_FreeSurface(debugScreen);

  SDL_DestroyTexture(sdlDebugTexture);
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_FreeSurface(screen);

  SDL_Quit();
}

void SDLUI::handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
          abort_event = true;
        }
        break;
      case SDL_QUIT:
        abort_event = true;
        break;
    }
  }
}

bool SDLUI::abortEvent() {
  return abort_event;
}
