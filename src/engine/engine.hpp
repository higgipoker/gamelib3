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

#include "../graphics/renderable.h"
#include "../physics/movable.hpp"
#include "../utils/timer.hpp"
#include "../camera/camera.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <set>

namespace gamelib3 {

enum class EntityType { Renderable, Movable };

/**
 * @brief manages unique ids for access to entities
 */
struct ID {
  static const int max_entities = 1000;
  std::set<int> moveable_ids;
  std::set<int> renderable_ids;

  /**
   * @brief get a unique id
   * @param type for which entity type
   * @return unique id or -1 if failed
   */
  int get_unique_id(EntityType type) {
    std::set<int> *list = nullptr;
    switch (type) {
      case EntityType::Movable:
        list = &moveable_ids;
        break;
      case EntityType::Renderable:
        list = &renderable_ids;
        break;
    }
    if (list) {
      for (int i = 0; i < max_entities; ++i) {
        if (std::find(list->begin(), list->end(), i) == list->end()) {
          list->insert(i);
          return i;
        }
      }
    }
    // ERROR!
    return -1;
  }

  /**
   * @brief frees up an id when an object is removed
   * @param type entity type
   * @param id id to free up
   */
  void free_unique_id(EntityType type, int id) {
    std::set<int> *list = nullptr;
    switch (type) {
      case EntityType::Movable:
        list = &moveable_ids;
        break;
      case EntityType::Renderable:
        list = &renderable_ids;
        break;
    }
    if (list) {
      list->erase(id);
    }
  }
};

/**
 * @brief a struct to manage constant frame rates
 */
struct FramerateData {
  /**
   * @brief how long left to do the current frame
   * @param target_frame_time desired frame time
   * @return time left
   */
  inline float time_left(float target_frame_time) {
    float newnewtime = gamestep_timer.GetLiveTime();
    float gametime = gamestep_timer.GetFrameTime();
    float frame_time = newnewtime - gametime;
    float target = target_frame_time * 1000;
    return target - frame_time;
  }
  Timer gamestep_timer;
  float fps = 0;
  float frames_this_second = 0;
  float lastTime = 0.0f;
  float fps_timer = 0.0f;
};

/**
 * @brief encapsulate id and entity
 */
struct MovablePair {
  int id;
  Movable entity;
};

/**
 * @brief encapsulate id and entity
 */
struct RenderablePair {
  int id;
  Renderable entity;
};

/**
 * @brief The Engine class
 */
class Engine {
 public:
  /**
   * @brief sets up the game
   * @param window_title
   * @param window_width
   * @param window_height
   * @param fullscreen
   * @param flags
   */
  void init(const std::string &window_title, int window_width,
            int window_height, bool fullscreen, int flags = sf::Style::Default);

  /**
   * @brief step one frame forward
   */
  void step();

  /**
   * @brief addRenderable
   * @param r
   * @return
   */
  int addRenderable(Renderable &r);

  /**
   * @brief addMovable
   * @param m
   * @return
   */
  int addMovable(Movable &m);

  /**
   * @brief remRenderable
   * @param id
   * @return
   */
  bool remRenderable(int id);

  /**
   * @brief remMovable
   * @param id
   * @return
   */
  bool remMovable(int id);

  /**
   * @brief getRenderable
   * @param id
   * @return
   */
  Renderable *getRenderable(int id);

  /**
   * @brief getMovable
   * @param id
   * @return
   */
  Movable *getMovable(int id);

  sf::RenderWindow window;
  sf::View main_view;

  /// track if still running
  bool running = true;

 private:
  void handle_input();
  void update_camera();
  void render();
  void update_physics(const float dt);

  std::vector<Renderable> render_list;
  std::vector<Movable> movable_list;

  ID id_manager;
  FramerateData framerate_manager;
};
}  // namespace gamelib3
