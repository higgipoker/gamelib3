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
#include "engine.hpp"
#include "../physics/integration.hpp"

#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <iostream>

namespace gamelib3 {

// target fps
static const float fps = 60.0f;

// target frame time
static const float target_frame_time = 1.0f / fps;

// physics timestep
const float Engine::timestep = 0.01f;

// -----------------------------------------------------------------------------
// plain old function to find video modes
// -----------------------------------------------------------------------------
static bool valid_videomode(int width, int height) {
  // get list of supported video modes
  std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

  // search for one that matched the requested width and height
  for (auto &mode : modes) {
    if (mode.width == width && mode.height == height) {
      return true;
    }
  }
  return false;
}

// -----------------------------------------------------------------------------
// init
// -----------------------------------------------------------------------------
void Engine::Init(const std::string &window_title, int window_width,
                  int window_height, bool fullscreen, int flags) {
  sf::VideoMode video_mode;
  video_mode.width = window_width;
  video_mode.height = window_height;
  if (fullscreen && valid_videomode(video_mode.width, video_mode.height)) {
    window.create(video_mode, window_title, sf::Style::Fullscreen);
  } else {
    sf::VideoMode vm = sf::VideoMode::getDesktopMode();
    vm.width = window_width;
    vm.height = window_height;
    window.create(vm, window_title, flags);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Engine::AddEntity(GameEntity *entity) { entity_list.push_back(entity); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Engine::remEntity(GameEntity *entity) {
  entity_list.erase(std::remove(entity_list.begin(), entity_list.end(), entity),
                    entity_list.end());
}

// -----------------------------------------------------------------------------
// step
// -----------------------------------------------------------------------------
void Engine::Step() {
  // for frame time counting
  framerate_manager.gamestep_timer.Update();

  // handle user inputs
  handle_input();

  // render
  render();

  int count = 0;

  // simulate while there is still time left for the frame
  while (framerate_manager.time_left(target_frame_time) >= 0) {
    update_physics(timestep);
    ++count;
  }
  std::cout << count << " updates" << std::endl;
}

// -----------------------------------------------------------------------------
// update_camera
// -----------------------------------------------------------------------------
void Engine::update_camera() {}

// -----------------------------------------------------------------------------
// render
// -----------------------------------------------------------------------------
void Engine::render() {
  window.clear(sf::Color::Blue);

  std::sort(entity_list.begin(), entity_list.end(), sort_entities);
  window.setView(camera.viewport);
  for (auto &entity : entity_list) {
    entity->graphical_aspect->Render(window);
  }

  window.display();
}

// -----------------------------------------------------------------------------
// update_physics
// -----------------------------------------------------------------------------
void Engine::update_physics(const float dt) {
  for (auto &entity : entity_list) {
    entity->physical_aspect->Step(timestep);
  }
}

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void Engine::handle_input() {
  static sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        running = false;
        break;
      case sf::Event::Resized:
        break;
      case sf::Event::LostFocus:
        break;
      case sf::Event::GainedFocus:
        break;
      case sf::Event::TextEntered:
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape) {
          if (window.hasFocus()) {
            running = false;
          }
        }
        break;
      case sf::Event::KeyReleased:
        break;
      case sf::Event::MouseWheelMoved:
        break;
      case sf::Event::MouseWheelScrolled:
        break;
      case sf::Event::MouseButtonPressed:
        break;
      case sf::Event::MouseButtonReleased:
        break;
      case sf::Event::MouseMoved:
        break;
      case sf::Event::MouseEntered:
        break;
      case sf::Event::MouseLeft:
        break;
      case sf::Event::JoystickButtonPressed:
        break;
      case sf::Event::JoystickButtonReleased:
        break;
      case sf::Event::JoystickMoved:
        break;
      case sf::Event::JoystickConnected:
        break;
      case sf::Event::JoystickDisconnected:
        break;
      case sf::Event::TouchBegan:
        break;
      case sf::Event::TouchMoved:
        break;
      case sf::Event::TouchEnded:
        break;
      case sf::Event::SensorChanged:
        break;
      case sf::Event::Count:
        break;
    }
  }
}
}  // namespace gamelib3
