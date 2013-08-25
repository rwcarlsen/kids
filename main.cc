
#include <iostream>
#include <cctype>
#include <locale>

#include "sdl/sdl.h"

static const char* kFontPath = "/usr/share/fonts/TTF/VeraBd.ttf";

int main(int argc, char** argv) {
  try {
    sdl::SDLinit init(SDL_INIT_EVERYTHING);

    int font_size = 500;
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
    bool big = true;
    std::string curr_k("A");
    sdl::Color curr_color = sdl::Color::purple();
    while (!done) {
      // process events
      while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
          done = true;
        } else if (ev.type == SDL_KEYDOWN) {
          if (ev.key.keysym.sym == SDLK_ESCAPE) {
            done = true;
          } else if (ev.key.keysym.sym == SDLK_SPACE) {
            big = !big;
            char c;
            if (big) {
              c = std::toupper(curr_k.c_str()[0]);
            } else {
              c = std::tolower(curr_k.c_str()[0]);
            }
            curr_k[0] = c;
          } else if (ev.key.keysym.sym == SDLK_RETURN) {
            
          } else {
            std::string tmp(SDL_GetKeyName(ev.key.keysym.sym));
            if (tmp.size() == 1 && std::isalnum(tmp.c_str()[0])) {
              curr_k = tmp;
            }
          }

        }
      }
      auto surf = font.RenderBlended(curr_k, curr_color);

      int sw = surf->width();
      int sh = surf->height();
      SDL_Rect dst = {(w - sw) / 2, (h - sh) / 2, sw, sh};

      ren.Clear();
      sdl::Texture tex(ren, *surf.get());
      tex.ApplyRects(NULL, &dst);
      ren.Render();
      SDL_Delay(20);
    }

    return 0;
  } catch (std::exception err) {
    std::cout << "ERROR: " << err.what() << "\n";
    return 1;
  }
}
