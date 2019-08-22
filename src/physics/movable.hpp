#pragma once

#include "../graphics/spriteanimation.hpp"

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
  virtual void Step(float dt);

  /**
   * @brief SetPosition
   * @param x
   * @param y
   */
  void SetPosition(int x, int y);

  /**
   * @brief addAnimation
   * @param a_sprite_anim
   */
  virtual void AddAnimation(const SpriteAnimation& a_sprite_anim);

  /**
   * @brief addAnimation
   * @param animname
   * @param frametime
   * @param loopanim
   * @param framelist
   */
  virtual void AddAnimation(const std::string& animname, const float frametime,
                            bool loopanim, std::vector<int> framelist);

  /**
   * @brief startAnimation
   * @param a_name
   */
  virtual void StartAnimation(const std::string& a_name);

  /**
   * @brief stopAnimation
   */
  virtual void StopAnimation();

  /**
   * @brief animate
   * @param in_dt
   */
  virtual void Animate(float in_dt);

  Vector3 position, velocity, force, friction;
  float mass = 1;
  float width = 1;
  Renderable* renderable = nullptr;
  bool valid = true;  // dummy sets this to false;

 protected:
  // since animations are timed, entity controls sprite anims
  /// // entity can animate its widget
  std::map<std::string, SpriteAnimation> animations;

  /// current running animation
  SpriteAnimation* current_animation = nullptr;
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
