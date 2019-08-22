#pragma once

#include "../math/vector.hpp"
#include "autotexture.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace gamelib3 {

class Renderable {
 public:
  Renderable() = default;

  /**
   * @brief Render
   * @param target
   */
  virtual void Render(sf::RenderTarget& target) = 0;

  /// z order
  int zorder = 0;

 protected:
  sf::Sprite sprite;
  AutoTexture texture;
  std::vector<sf::IntRect> rects;
  int id = -1;
  float image_width = 0;
  float image_height = 0;
  float sprite_scale_factor = 0;
};

}  // namespace gamelib3
