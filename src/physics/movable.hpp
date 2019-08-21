#pragma once
#include "../graphics/renderable.h"
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

 protected:
  Vector3 position, velocity, force, friction;
  float mass = 1;
};
}  // namespace gamelib3
