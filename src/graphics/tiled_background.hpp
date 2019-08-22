#pragma once
#include "sprite.hpp"

namespace gamelib3 {

class TiledBackground : public Sprite {
 public:
  /**
   * @brief TiledBackground
   * @param imagefile
   * @param world_rect
   */
  TiledBackground(const std::string& imagefile, const sf::IntRect& world_rect);
};

}  // namespace gamelib3
