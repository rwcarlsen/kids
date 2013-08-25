
#ifndef SOUND_H_
#define SOUND_H_

#include "SDL2/SDL_mixer.h"

#include "sdl/error.h"

namespace sdl {

class Sound {
 public:
  Sound(std::string fpath) throw(FatalErr) : chunk_(nullptr) {
    chunk_ = Mix_LoadWAV(fpath.c_str());
    if (chunk_ == nullptr) {
      throw(FatalErr(Mix_GetError()));
    }
  };

  ~Sound() {
    Mix_FreeChunk(chunk_);
  };

  Sound(const Sound& what) = delete;

  void Play() {
    if (Mix_PlayChannel(-1, chunk_, 0) == -1) {
      throw(FatalErr(Mix_GetError()));
    }
  };

 private:
  Mix_Chunk* chunk_;
};

} // namespace sdl

#endif
