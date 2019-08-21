#include "integration.hpp"
#include "metrics.h"

#include "../math/vector.hpp"

namespace gamelib3{
// -----------------------------------------------------------------------------
// improved_euler
// -----------------------------------------------------------------------------
void integrate_improved_euler(Movable &movable, float timestep) {
  // step 1
  movable.force =
      (movable.force - (movable.velocity.multiply(movable.friction)));
  Vector3 acceleration = movable.force / movable.mass;
  Vector3 k1 = acceleration * timestep;

  // step 2
  movable.force =
      (movable.force - (movable.velocity + k1).multiply(movable.friction));
  acceleration = movable.force / movable.mass;
  Vector3 k2 = acceleration * timestep;

  // update entity.movable.velocity
  movable.velocity = movable.velocity + (k1 + k2) / 2;

  // change in position (converted to pixels)
  Vector3 dp = MetersToPixels(movable.velocity * timestep);

  // apply new position
  movable.position = movable.position + dp;
}
}