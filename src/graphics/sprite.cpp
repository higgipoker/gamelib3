#include "sprite.hpp"
#include "../physics/metrics.hpp"
#include "../physics/movable.hpp"

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
void Sprite::Render(sf::RenderTarget &target) {
  if (physical->valid) {
    Perspectivize(physical->position.z, physical->width, 20);
  }
  target.draw(sprite);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sprite::SetPosition(int x, int y) { sprite.setPosition(x, y); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sprite::SetPosition(Vector3 position) {
  sprite.setPosition(position.x, position.y);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sprite::Move(int x, int y) { sprite.move(x, y); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Sprite::Perspectivize(float z, float width, float camera_height) {
  // size depending on distance from camera
  float dimensions = width;
  float dist_from_camera = camera_height - z;
  float angular_diameter = 2 * (atanf(dimensions / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float sprite_scale_factor = degs / dimensions;
  float sprite_ratio = dimensions / image_width;
  sprite_scale_factor *= sprite_ratio;
  sprite.setScale(sprite_scale_factor, sprite_scale_factor);

  // y offset due to height
  float z_cm = z * CM_PER_PIXEL;

  if (Floats::greater_than(z_cm, 0)) {
    float y_offset = Y_OFFSET_DUE_TO_HEIGHT * z_cm;
    sprite.move(0, -y_offset);
  }
}
}  // namespace gamelib3
