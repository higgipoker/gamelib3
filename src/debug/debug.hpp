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

#include "../dll_export.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>

#include <deque>

namespace gamelib3 {
class Engine;
class Debug {
 public:
  /**
   * @brief Debug
   * @param in_game
   */
  Debug(Engine &_engine);

  /**
   * @brief ~Debug
   */
  virtual ~Debug();

  /**
   * @brief update
   */
  virtual void update();

  /**
   * @brief render
   */
  void render();

  /**
   * @brief onClose
   */
  virtual void onClose();

  // data for fps display
  std::deque<float> fps_history;

 protected:

  // status
  EXPORTED static bool active;

  // inited flag
  static bool inited;

  // dimensions
  sf::FloatRect panel_dimensions;

  Engine &engine;

  // widget data
  float shown_fps = 0;
  float fps_min = 1000;
  float fps_max = 0;
  int frame_count = 0;
  sf::Clock ui_clock;
};

}  // namespace gamelib2
