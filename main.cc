
#include <iostream>
#include <cctype>

#include "sdl/sdl.h"

#include "letters.h"

static const char* kFontPath = "/usr/share/fonts/TTF/VeraBd.ttf";

int main(int argc, char** argv) {
  try {
    sdl::SDLinit init(SDL_INIT_EVERYTHING);

    // create window and renderer
    int w = 850;
    int h = 650;
    sdl::Window win("Letters", 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    win.Show();
    sdl::Renderer ren(win, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(ren.raw(), w, h);

    // start up the main loop
    SDL_Event ev;
    bool done = false;
    Letters letters(kFontPath, &ren);
    while (!done) {
      // process events
      while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
          done = true;
        } else if (ev.type == SDL_KEYDOWN) {
          if (ev.key.keysym.sym == SDLK_ESCAPE) {
            done = true;
          } else if (ev.key.keysym.sym == SDLK_SPACE) {
            letters.ToggleCase();
          } else if (ev.key.keysym.sym == SDLK_RETURN) {
            letters.NextColor();
          } else {
            std::string s(SDL_GetKeyName(ev.key.keysym.sym));
            if (s.size() == 1 && std::isalnum(s.c_str()[0])) {
              letters.set_text(s);
            }
          }
        }
      }

      letters.Render();
      SDL_Delay(20);
    }

    return 0;
  } catch (std::exception err) {
    std::cout << "ERROR: " << err.what() << "\n";
    return 1;
  }
}
