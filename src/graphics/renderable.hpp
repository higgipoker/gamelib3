#pragma once

#include "../math/vector.hpp"
#include "autotexture.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <vector>

namespace gamelib3 {

/**
 * @brief The AnchorType enum
 */
enum class AnchorType {
  None,
  TopLeft,
  TopRight,
  BottomRight,
  BottomLeft,
  TopCenter,
  BottomCenter,
  Center
};

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

  /**
   * @brief AddPrimitive
   * @param primitive
   */
  void AddPrimitive(sf::Shape* primitive);

  /// z order
  int zorder = 0;

 protected:
  /**
   * @brief render_primitives
   * @param target
   */
  void render_primitives(sf::RenderTarget& target);

  /**
   * @brief render_bounds
   */
  void render_bounds(sf::RenderTarget& target);

  /**
   * @brief anchor
   */
  void anchor();

  /// track position
  Vector3 position;

  /// actual bounds on screen after transforms
  sf::FloatRect bounds;

  /// a list of primitives to draw
  std::vector<sf::Shape*> primitives;

  /// origin of image for displaying
  AnchorType origin = AnchorType::Center;

  /// dimensions of what is being drawn to screen
  float render_width = 0;
  float render_height = 0;
};

}  // namespace gamelib3
