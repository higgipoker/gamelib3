#include "spriteanimation.hpp"

#include <iostream>

namespace gamelib3 {

// -----------------------------------------------------------------------------
// SpriteAnimation
// -----------------------------------------------------------------------------
SpriteAnimation::SpriteAnimation(const std::string &a_id, float a_frametime,
                                 bool a_loop, std::vector<int> &a_frames,
                                 Sprite *in_widget)
    : name(a_id),
      frames(a_frames),
      current_frame(frames.begin()),
      loop(a_loop),
      frame_time(a_frametime),
      sprite(in_widget) {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SpriteAnimation::ConnectSprite(Sprite *in_sprite) { sprite = in_sprite; }

// -----------------------------------------------------------------------------
// start
// -----------------------------------------------------------------------------
void SpriteAnimation::Start() {
  current_frame = frames.begin();
  counter = 0;
  running = true;
}

// -----------------------------------------------------------------------------
// step
// -----------------------------------------------------------------------------
int SpriteAnimation::Update(float in_dt) {
  if (running) {
    counter += in_dt;
    if (counter > frame_time) {
      counter = 0;

      if (++current_frame == frames.end()) {
        if (loop) {
          current_frame = frames.begin();
        } else {
          running = false;
          --current_frame;
        }
      }
    }
    if (sprite) {
      sprite->SetFrame(*current_frame);
    }
  }
  return *current_frame;
}

// -----------------------------------------------------------------------------
// stop
// -----------------------------------------------------------------------------
void SpriteAnimation::Stop() { running = false; }

// -----------------------------------------------------------------------------
// setStpeed
// -----------------------------------------------------------------------------
void SpriteAnimation::SetStpeed(int a_speed) {
  frame_time = static_cast<float>(a_speed);
}

// -----------------------------------------------------------------------------
// currentFrame
// -----------------------------------------------------------------------------
int SpriteAnimation::CurrentFrame() { return *current_frame; }

// -----------------------------------------------------------------------------
// finished
// -----------------------------------------------------------------------------
bool SpriteAnimation::Finished() {
  if (!loop) {
    return !running;
  }
  return false;
}

}  // namespace gamelib3
