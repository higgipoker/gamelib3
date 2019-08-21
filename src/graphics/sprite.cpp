#include "sprite.hpp"

namespace gamelib3 {

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Sprite::Sprite(const std::string &spritesheet, int rows, int cols) {
  Init(spritesheet, rows, cols);
}

// -----------------------------------------------------------------------------
// init_sprite
// -----------------------------------------------------------------------------
void Sprite::Init(const std::string &spritesheet, int rows, int cols) {
  texture.Initialize(std::move(spritesheet));
  sprite.setTexture(texture());
  image_width = texture().getSize().x / static_cast<float>(cols);
  image_height = texture().getSize().y / static_cast<float>(rows);

  // set up the coordinates of each frame
  float sprite_width = static_cast<float>(texture().getSize().x / cols);
  float sprite_height = static_cast<float>(texture().getSize().y / rows);

  sprite.setOrigin(sprite_width / 2, sprite_height / 2);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      sf::IntRect rect(static_cast<int>(col * sprite_width),
                       static_cast<int>(row * sprite_height),
                       static_cast<int>(sprite_width),
                       static_cast<int>(sprite_height));
      rects.push_back(rect);
    }
  }
  sprite.setTextureRect(rects[0]);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sprite::Render(sf::RenderTarget &target) { target.draw(sprite); }
}  // namespace gamelib3
