/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
#pragma once

#include "../camera/camera.hpp"
#include "../debug/debug.hpp"
#include "../graphics/renderable.hpp"
#include "../input/gamepad.hpp"
#include "../input/input.hpp"
#include "../physics/movable.hpp"
#include "../utils/timer.hpp"
#include "entity.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <set>
namespace gamelib3 {

/**
 * @brief a struct to manage constant frame rates
 */
struct FramerateData {
  FramerateData() { second_timer.restart(); }
  /**
   * @brief on_frame_started
   */
  inline void on_frame_started() {
    gamestep_timer.restart();
    frame_start_time =
        static_cast<float>(gamestep_timer.getElapsedTime().asMilliseconds());
  }

  /**
   * @brief on_frame_ended
   */
  inline void on_frame_ended() {
    float elapsed = second_timer.getElapsedTime().asMilliseconds();
    framecount++;
    if (elapsed >= 1000) {
      fps = framecount;
      framecount = 0;
      second_timer.restart();
      // std::cout << "frames: " << fps << std::endl;
    }
  }

  /**
   * @brief how long left to do the current frame
   * @param target_frame_time desired frame time
   * @return time left
   */
  inline float time_left(float target_frame_time) {
    float newnewtime =
        static_cast<float>(gamestep_timer.getElapsedTime().asMilliseconds());
    float frame_time = newnewtime - frame_start_time;
    float target = target_frame_time * 1000;
    return target - frame_time;
  }
  sf::Clock gamestep_timer;
  sf::Clock second_timer;
  float frame_start_time = 0;
  float framecount = 0;
  float fps = 0;
};

/**
 * @brief The Engine class
 */
class Engine {
 public:
  /**
   * @brief Engine
   */
  Engine();

  /**
   */
  ~Engine();

  /**
   * @brief Shutdown
   */
  void Shutdown();

  /**
   * @brief sets up the game
   * @param window_title
   * @param window_width
   * @param window_height
   * @param fullscreen
   * @param flags
   */
  void Init(const std::string &window_title, int window_width,
            int window_height, bool fullscreen, int flags = sf::Style::Default);

  /**
   * @brief step one frame forward
   */
  void Step();

  /**
   * @brief addEntity
   * @param enitty
   */
  void AddEntity(GameEntity *entity);

  /**
   * @brief remEntity
   * @param entity
   */
  void remEntity(GameEntity *entity);

  /**
   * @brief registerInputCallback
   * @param callback
   */
  void registerInputCallback(InputCallback *callback);

  sf::RenderWindow window;
  Camera camera;
  bool paused = false;

  /// track if still running
  bool running = true;

  /// physics time step
  static const float timestep;

 private:
  void handle_input();
  void update_camera();
  void render();
  void update_physics(const float dt);

  std::vector<GameEntity *> entity_list;
  std::vector<InputCallback *> input_callbacks;

  FramerateData framerate_manager;
  //  Debug debug;
  sf::Clock ui_clock;
  Gamepad gamepad;
};
}  // namespace gamelib3
