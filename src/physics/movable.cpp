#include "movable.hpp"

#include "../graphics/renderable.hpp"
#include "metrics.hpp"

namespace gamelib3 {
Movable::~Movable() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Movable::Step(float dt) {
  integrate_euler(dt);
  Animate(dt);
}

/**
 * @brief Movable::SetPosition
 * @param x
 * @param y
 */
void Movable::SetPosition(int x, int y) {
  position.x = x;
  position.y = y;
}

// -----------------------------------------------------------------------------
// integrate_improved_euler
// -----------------------------------------------------------------------------
void Movable::integrate_improved_euler(float dt) {
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

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Movable::AddAnimation(const SpriteAnimation &a_sprite_anim) {
  animations.insert(
      std::make_pair(a_sprite_anim.name, std::move(a_sprite_anim)));
}

// ----------------------------------------------------------------------------------
// AddAnimation
// ----------------------------------------------------------------------------------
void Movable::AddAnimation(const std::string &animname, const float frametime,
                           bool loopanim, std::vector<int> framelist) {
  Sprite *sprite = static_cast<Sprite *>(renderable);
  SpriteAnimation anim(animname, frametime, loopanim, framelist, sprite);
  AddAnimation(anim);
}

// -----------------------------------------------------------------------------
// Animate
// -----------------------------------------------------------------------------
void Movable::Animate(float in_dt) {
  if (current_animation) {
    current_animation->Update(in_dt);
  }
}
// -----------------------------------------------------------------------------
// StartAnimation
// -----------------------------------------------------------------------------
void Movable::StartAnimation(const std::string &a_name) {
  if (current_animation && a_name == current_animation->name) return;
  if (animations.find(a_name) != animations.end()) {
    current_animation = &(animations.find(a_name)->second);
    current_animation->Start();
  }
}

// -----------------------------------------------------------------------------
// StopAnimation
// -----------------------------------------------------------------------------
void Movable::StopAnimation() {
  if (current_animation) {
    current_animation->Stop();
    current_animation = nullptr;
  }
}
}  // namespace gamelib3
