#pragma once

#include "../math/vector.hpp"
namespace gamelib3 {

class Renderable;

class Movable {
 public:
  Movable() = default;
  /**
   * @brief ~Movable
   */
  virtual ~Movable();

  /**
   * @brief Step
   * @param dt
   */
  virtual void Step(float dt) = 0;

  Vector3 position, velocity, force, friction;
  float mass = 1;
  float width = 1;
  Renderable *renderable = nullptr;
  bool valid = true; // dummy sets this to false;

 protected:
  /**
   * @brief integrate_euler
   * @param dt
   */
  void integrate_euler(float dt);

  /**
   * @brief integrate_improved_euler
   * @param dt
   */
  void integrate_improved_euler(float dt);
};
}  // namespace gamelib3
