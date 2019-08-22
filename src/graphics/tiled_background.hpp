#pragma once
#include "renderable.hpp"

namespace gamelib3{

class TiledBackground : public Renderable {
public:
  TiledBackground(const std::string& imagefile, const sf::IntRect& world_rect) {
    texture.Initialize(imagefile);
    texture().setRepeated(true);
    sprite.setTexture(texture());
    sprite.setTextureRect(world_rect);
    zorder = 0;
  }
  virtual void Render(sf::RenderTarget& target) override {
    target.draw(sprite);
  }

};

}
