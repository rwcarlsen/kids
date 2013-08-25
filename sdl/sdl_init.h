
#ifndef SDL_INIT_H_
#define SDL_INIT_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

namespace sdl {

class SDLinit {
 public:
  SDLinit(uint32_t flags = 0) throw(FatalErr) {
    if (SDL_Init(flags) != 0) {
      throw FatalErr();
    }
    if (TTF_Init() != 0) {
      throw FatalErr(TTF_GetError());
    }
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
      throw FatalErr(Mix_GetError());
    }
  };

  ~SDLinit() {
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
  };

  SDLinit(const SDLinit& what) = delete;
};

} // namespace sdl

#endif
