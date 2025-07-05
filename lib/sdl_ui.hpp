#include "common.hpp"
#include "framebuffer.hpp"

class SDLUI {
 private:
  const u16 SCREEN_WIDTH = 1024U;
  const u16 SCREEN_HEIGHT = 768U;
  const u8 scale = 2U;
  bool abort_event = false;

 public:
  SDLUI();
  ~SDLUI();

  void handleEvents();
  bool abortEvent();

  void renderFrame(Framebuffer &fb);
};
