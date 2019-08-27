#include "movable.hpp"

#include "../graphics/renderable.hpp"
#include "metrics.hpp"

#include <iostream>

namespace gamelib3 {
Movable::~Movable() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Movable::Step(float dt) {
  integrate_improved_euler(dt);
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
  force = (force - (velocity.multiply2d(co_friction * dt)));
  Vector3 acceleration = force / mass;
  Vector3 k1 = acceleration * dt;

  // step 2
  force = (force - (velocity + k1).multiply2d(co_friction));
  acceleration = force / mass;
  Vector3 k2 = acceleration * dt;

  // update velocity
  velocity = velocity + (k1 + k2) / 2;

  // change in position (converted to pixels)
  Vector3 dp = (velocity * dt);

  // apply new position
  position = position + dp;

  force.reset();
}

// -----------------------------------------------------------------------------
// euler_integration
// -----------------------------------------------------------------------------
void Movable::integrate_euler(float dt) {
  force = (force - (velocity.multiply2d(co_friction * dt)));
  Vector3 acceleration = force / mass;
  Vector3 old_velocity = velocity;
  velocity = velocity + acceleration * dt;
  Vector3 dp = (old_velocity + velocity) * 0.5 * dt;
  position = position + (dp);
  force.reset();
}

// -----------------------------------------------------------------------------
// addAnimation
// -----------------------------------------------------------------------------
void Movable::AddAnimation(const SpriteAnimation &a_sprite_anim) {
  animations.insert(std::make_pair(a_sprite_anim.name, a_sprite_anim));
}

// ----------------------------------------------------------------------------------
// AddAnimation
// ----------------------------------------------------------------------------------
void Movable::AddAnimation(const std::string &animname, const float frametime,
                           bool loopanim, std::vector<int> framelist) {
  Sprite *sprite = dynamic_cast<Sprite *>(renderable);
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
