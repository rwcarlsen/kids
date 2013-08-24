
#include <iostream>

#include "sdl/sdl.h"

static const char* kFontPath = "/usr/share/fonts/TTF/DejaVuSerif-Bold.ttf";

int main(int argc, char** argv) {
  try {
    sdl::SDLinit init(SDL_INIT_EVERYTHING);

    int font_size = 144;
    sdl::Font font(kFontPath, font_size);

    // create window and renderer
    int w = 850;
    int h = 650;
    sdl::Window win("Letters", 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    win.Maximize();
    win.Center();
    win.Show();
    sdl::Renderer ren(win, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(ren.raw(), w, h);

    // start up the main loop
    SDL_Event ev;
    bool done = false;
    while (!done) {
      // process events
      while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
          done = true;
        } else if (ev.type == SDL_KEYDOWN) {
          if (ev.key.keysym.sym == SDLK_ESCAPE) {
            done = true;
          }
          const char* k = SDL_GetKeyName(ev.key.keysym.sym);
          auto surf = font.RenderBlended(std::string(k), sdl::Color::purple());

          int sw = surf->width() * 3;
          int sh = surf->height() * 3;
          SDL_Rect dst = {(w - sw) / 2, (h - sh) / 2, sw, sh};

          ren.Clear();
          sdl::Texture tex(ren, *surf.get());
          tex.ApplyRects(NULL, &dst);
          ren.Render();
        }
      }
      SDL_Delay(20);
    }

    return 0;
  } catch (std::exception err) {
    std::cout << "ERROR: " << err.what() << "\n";
    return 1;
  }
}
