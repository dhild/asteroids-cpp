#ifndef ASTEROIDS_SIMPLETEXTOVERLAY_HPP
#define ASTEROIDS_SIMPLETEXTOVERLAY_HPP

#include "../rendering.hpp"

namespace rendering {

  class DrawableTextOverlay : public TextOverlay {
  public:
    virtual ~DrawableTextOverlay() override {};

    virtual void draw() const = 0;
  };

  std::shared_ptr<DrawableTextOverlay> create_text_overlay();

}

#endif //ASTEROIDS_SIMPLETEXTOVERLAY_HPP
