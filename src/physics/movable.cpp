#include "movable.hpp"

#include "metrics.hpp"

namespace gamelib3 {
Movable::~Movable() {}

// -----------------------------------------------------------------------------
// integrate_improved_euler
// -----------------------------------------------------------------------------
void Movable::integrate_improved_euler(float dt){
  // step 1
  force = (force - (velocity.multiply(friction)));
  Vector3 acceleration = force / mass;
  Vector3 k1 = acceleration * dt;

  // step 2
  force = (force - (velocity + k1).multiply(friction));
  acceleration = force / mass;
  Vector3 k2 = acceleration * dt;

  // update entity.velocity
  velocity = velocity + (k1 + k2) / 2;

  // change in position (converted to pixels)
  Vector3 dp = MetersToPixels(velocity * dt);

  // apply new position
  position = position + dp;
}

// -----------------------------------------------------------------------------
// euler_integration
// -----------------------------------------------------------------------------
void Movable::integrate_euler(float dt) {
  // drag
  force = (force - (velocity.multiply(friction)));

  // acceleration = force / mass
  Vector3 acceleration = force / mass;

  // difference in velocity = acceleration * difference time
  Vector3 dv = acceleration * dt;

  // velocity = velocity + difference in velocity
  velocity += dv;

  // difference in position = velocity * difference time
  Vector3 dp = velocity * dt;

  // convert to pixels
  dp = MetersToPixels(dp);

  // update position
  position += dp;
}
}  // namespace gamelib3
