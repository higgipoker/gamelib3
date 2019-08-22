#pragma once

#include "../math/vector.hpp"
#include "autotexture.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace gamelib3 {

class Movable;

class Renderable {
 public:
  Renderable() = default;

  /**
   * @brief Render
   * @param target
   */
  virtual void Render(sf::RenderTarget& target) = 0;

  /**
   * @brief SetPosition
   * @param x
   * @param y
   */
  virtual void SetPosition(int x, int y) = 0;

  /**
   * @brief SetPosition
   * @param position
   */
  virtual void SetPosition(Vector3 position) = 0;

  /**
   * @brief move
   */
  virtual void Move(int x, int y) = 0;

  /**
   * @brief Perspectivize
   * @param z
   * @param distance_from_camera
   */
  virtual void Perspectivize(float z, float width, float camera_height) = 0;

  /// z order
  int zorder = 0;

  /// access t physical aspect
  Movable *physical;
};

}  // namespace gamelib3
