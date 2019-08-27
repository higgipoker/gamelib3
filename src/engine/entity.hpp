#pragma once

#include "../graphics/renderable.hpp"
#include "../input/controller.hpp"
#include "../physics/movable.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <set>

namespace gamelib3 {

/**
 * @brief For easy creation of entities without a real movable (only graphic)
 */
class DummyMovable : public Movable {
 public:
  /**
   * @brief Movable
   */
  DummyMovable() { valid = false; }
  /**
   * @brief Step
   * @param dt
   */
  void Step(float dt) override {}

  /**
   * @brief PopulateAnimations
   */
  void PopulateAnimations() override{};
};

/**
 * @brief For easy creation of entities without a real graphic (only movable)
 */
class DummyRenderable : public Renderable {
 public:
  /**
   * @brief Render
   * @param target
   */
  void Render(sf::RenderTarget& target) override {}

  /**
   * @brief SetPosition
   * @param x
   * @param y
   */
  void SetPosition(int x, int y) override{};

  /**
   * @brief SetPosition
   * @param position
   */
  void SetPosition(Vector3 position) override{};

  /**
   * @brief move
   */
  void Move(int x, int y) override{};

  /**
   * @brief Perspectivize
   * @param z
   * @param distance_from_camera
   */
  void Perspectivize(float z, float width,
                     float distance_from_camera) override{};
};

class GameEntity {
 public:
  /**
   * @brief GameEntity
   * @param m
   * @param r
   */
  GameEntity(Movable* m, Renderable* r);

  /**
   * @brief GameEntity
   * @param m
   */
  GameEntity(Movable* m);

  /**
   * @brief GameEntity
   * @param r
   */
  GameEntity(Renderable* r);

  /**
   * @brief ~GameEntity
   */
  virtual ~GameEntity();

  /// the physical aspect
  Movable* physical_aspect = nullptr;

  /// the graphical aspect
  Renderable* graphical_aspect = nullptr;

  Controller* controller = nullptr;

 private:
  /// dummy for creating entities with only a graphical aspect
  static DummyMovable dummy_movable;

  /// dummy for creating entities with only a physical aspect
  static DummyRenderable dummy_renderable;
};

// -----------------------------------------------------------------------------
// sort_entities
// -----------------------------------------------------------------------------
inline bool sort_entities(const GameEntity* r1, const GameEntity* r2) {
  if (r1->graphical_aspect && r2->graphical_aspect) {
    return r1->graphical_aspect->zorder < r2->graphical_aspect->zorder;
  }
  return false;
}
}  // namespace gamelib3
