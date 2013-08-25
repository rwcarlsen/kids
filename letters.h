
#ifndef LETTERS_H_
#define LETTERS_H_

#include <algorithm>
#include <string>
#include <vector>

#include "sdl/sdl.h"

#define FONT_SIZE 400

class Letters {
 public:
  Letters(std::string font_path, sdl::Renderer* ren)
    : font_(font_path, FONT_SIZE),
      font_scale_(1),
      ren_(ren),
      color_(0),
      isupper_(true),
      text_("A") {
    colors_.push_back(sdl::Color::red());
    colors_.push_back(sdl::Color::blue());
    colors_.push_back(sdl::Color::green());
  };

  void NextColor() {
    color_++;
  };

  void ToggleCase() {
    isupper_ = !isupper_;
    set_text(text_);
  };

  void set_text(std::string s) {
    text_ = s;
    if (isupper_) {
      std::transform(text_.begin(), text_.end(), text_.begin(), ::toupper);
    } else {
      std::transform(text_.begin(), text_.end(), text_.begin(), ::tolower);
    }
  };

  void set_font_scale(double s) {
    font_scale_ = s;
  };

  double font_scale() {
    return font_scale_;
  };

  void Render() {
    auto surf = font_.RenderBlended(text_, colors_[color_ % colors_.size()]);

    int sw = surf->width() * font_scale_;
    int sh = surf->height() * font_scale_;
    int w, h;
    SDL_RenderGetLogicalSize(ren_->raw(), &w, &h);

    SDL_Rect dst = {(w - sw) / 2, (h - sh) / 2, sw, sh};
    sdl::Texture tex(*ren_, *surf.get());

    ren_->Clear();
    tex.ApplyRects(NULL, &dst);
    ren_->Render();
  };

 private:
  double font_scale_;
  std::string text_;
  std::vector<sdl::Color> colors_;
  int color_;
  bool isupper_;
  sdl::Font font_;
  sdl::Renderer* ren_;
};

#undef FONT_SIZE

#endif
