#include "tiled_background.hpp"

namespace gamelib3 {

TiledBackground::TiledBackground(const std::string& imagefile,
                                 const sf::IntRect& world_rect) {
  texture.Initialize(imagefile);
  texture().setRepeated(true);
  sprite.setTexture(texture());
  sprite.setTextureRect(world_rect);
  zorder = 0;
}

}  // namespace gamelib3
