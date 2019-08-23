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
#include "debug.hpp"

#include "../engine/engine.hpp"
#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"

#include <iostream>
#include <sstream>

namespace gamelib3 {

bool Debug::active = true;
bool Debug::inited = false;

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Debug::Debug(Engine &_engine) : engine(_engine) {
  ImGui::SFML::Init(engine.window);
}

Debug::~Debug() { ImGui::SFML::Shutdown(); }

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Debug::update() {
  inited = true;

  ImGui::SFML::Update(engine.window, ui_clock.restart());
  // ImGui::ShowDemoWindow();

  // global debug window
  ImGui::Begin("Debug");

  //  ImGui::SameLine();
  //  {  // pause
  //    ImGui::Checkbox("Pause", &engine.paused);
  //  }  // end pause

  {  // fps
    std::vector<float> values;
    float cnt = 0;
    fps_min = 1000;
    fps_max = 0;
    for (auto &val : fps_history) {
      values.push_back(val);
      cnt += val;
      if (val < fps_min) {
        fps_min = val;
      }
      if (val > fps_max) {
        fps_max = val;
      }
    }
    std::ostringstream title;
    title << "(past " << fps_history.size() << " seconds)";
    if (values.size()) {
      if (fabsf(values.back() - shown_fps) > 1) {
        shown_fps = values.back();
      }

      ImGui::Text("%i%s", static_cast<int>(shown_fps), " FPS");
      float avg = static_cast<float>(cnt / values.size());
      std::ostringstream capt;
      ImGui::PlotLines("##fps", values.data(), static_cast<int>(values.size()),
                       0, title.str().c_str(), avg - 6, avg + 15,
                       ImVec2(panel_dimensions.width, 50));
    }
  }  // end fps

  ImGui::End();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Debug::render() {
  if (inited && active) {
    ImGui::SFML::Render(engine.window);
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Debug::onClose() { ImGui::SFML::Render(engine.window); }
}  // namespace gamelib3
