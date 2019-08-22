#pragma once
#include "../graphics/renderable.hpp"
#include "../math/vector.hpp"
namespace gamelib3 {
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

 protected:
  void integrate_euler(float dt);
  void integrate_improved_euler(float dt);
};
}  // namespace gamelib3
