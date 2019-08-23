#include "gamepad.hpp"

#include <SFML/Window/Joystick.hpp>
#include <cstddef>

namespace gamelib3 {
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Gamepad::Gamepad() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Gamepad::on_poll() {
  if (sf::Joystick::isConnected(sf_joystick_index)) {
    //
    // dpad
    //
    states[static_cast<size_t>(InputState::Up)] =
        states[static_cast<size_t>(InputState::Down)] =
            states[static_cast<size_t>(InputState::Left)] =
                states[static_cast<size_t>(InputState::Right)] = 0;

    // left
    states[static_cast<size_t>(InputState::Left)] =
        sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::DpadLeft]) ||
        LeftThumbstick().x < -thumbstick_threshold;

    // right
    states[static_cast<size_t>(InputState::Right)] =
        sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::DpadRight]) ||
        LeftThumbstick().x > thumbstick_threshold;

    // up
    states[static_cast<size_t>(InputState::Up)] =
        sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::DpadUp]) ||
        LeftThumbstick().y < -thumbstick_threshold;

    // down
    states[static_cast<size_t>(InputState::Down)] =
        sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::DpadDown]) ||
        LeftThumbstick().y > thumbstick_threshold;

    //
    // buttons
    //

    // a
    states[static_cast<size_t>(InputState::FireUp)] = 0;
    if (sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::A])) {
      if (states[static_cast<size_t>(InputState::FireDown)] == 0) {
        states[static_cast<size_t>(InputState::FireDown)] = 1;
        fire_ticks[0] = 0;
      } else {
        states[static_cast<size_t>(InputState::FireLength)] = fire_ticks[0]++;
      }
    } else if (states[static_cast<size_t>(InputState::FireDown)] == 1) {
      states[static_cast<size_t>(InputState::FireUp)] = 1;
      states[static_cast<size_t>(InputState::FireDown)] = 0;
      states[static_cast<size_t>(InputState::FireLengthCached)] = fire_ticks[0];
      states[static_cast<size_t>(InputState::FireLength)] = 0;
    }

    // b
    states[static_cast<size_t>(InputState::FireUp2)] = 0;
    if (sf::Joystick::isButtonPressed(sf_joystick_index,
                                      button_map[ButtonNames::B])) {
      if (states[static_cast<size_t>(InputState::FireDown2)] == 0) {
        states[static_cast<size_t>(InputState::FireDown2)] = 1;
        fire_ticks[1] = 0;
      } else {
        states[static_cast<size_t>(InputState::FireLength2)] = fire_ticks[1]++;
      }
    } else if (states[static_cast<size_t>(InputState::FireDown2)] == 1) {
      states[static_cast<size_t>(InputState::FireUp2)] = 1;
      states[static_cast<size_t>(InputState::FireDown2)] = 0;
      states[static_cast<size_t>(InputState::FireLengthCached2)] =
          fire_ticks[1];
      states[static_cast<size_t>(InputState::FireLength2)] = 0;
    }
  }
}

}  // namespace gamelib3
