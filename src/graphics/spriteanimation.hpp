#pragma once

#include "sprite.hpp"

#include <string>
#include <vector>

namespace gamelib3 {

/**
 * @brief a sprite animatio is just a lst of frames and a speed
 */
class SpriteAnimation {
 public:
  /**
   * @brief SpriteAnimation
   * @param a_id
   * @param a_frametime
   * @param a_loop
   * @param a_frames
   * @param in_widget
   */
  SpriteAnimation(const std::string& a_id, float a_frametime, bool a_loop,
                  std::vector<int>& a_frames, Sprite* in_widget = nullptr);

  /**
   * @brief connectSprite
   * @param in_sprite
   */
  void ConnectSprite(Sprite* in_sprite);

  /**
   * @brief start
   */
  void Start();

  /**
   * @brief update
   * @param in_dt
   * @return
   */
  int Update(float in_dt);

  /**
   * @brief stop
   */
  void Stop();

  /**
   * @brief setStpeed
   * @param a_seped
   */
  void SetStpeed(int a_speed);

  /**
   * @brief currentFrame
   * @return
   */
  int CurrentFrame();

  /**
   * @brief finished
   * @return
   */
  bool Finished();

  std::string name;

 private:
  // the sprite to operate on
  Sprite* sprite = nullptr;

  // list of frame numbers
  std::vector<int> frames;

  // point to current frame
  std::vector<int>::iterator current_frame;

  // is a looping animation
  bool loop = false;

  // animation is still running
  bool running = false;

  // time of a frame
  float frame_time = 0;

  // frame timer
  float counter = 0;
};
}  // namespace gamelib3
