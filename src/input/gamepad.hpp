#pragma once
#include "controller.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>
#include <map>
namespace gamelib3 {

/**
 * @brief The ButtonNames enum
 */
enum class ButtonNames {
  A,
  B,
  X,
  Y,
  LeftBumper,
  RightBumper,
  LeftTrigger,
  RightTrigger,
  LeftTriggerValue,
  RightTriggerValue,
  Back,
  Start,
  XBOX,
  LeftThumbClick,
  RightThumbClick,
  DpadUp,
  DpadRight,
  DpadDown,
  DpadLeft,
};

using ButtonID = unsigned int;

/**
 * @brief The Gamepad class
 */
class Gamepad : public Controller {
 public:
  /**
   * @brief Gamepad
   */
  Gamepad();

 protected:
  /**
   * @brief Poll
   */
  void on_poll() override;

  inline sf::Vector2f LeftThumbstick() {
    return {sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::X),
            sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::Y)};
  }
  inline sf::Vector2f RightThumbstick() {
    return {sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::U),
            sf::Joystick::getAxisPosition(sf_joystick_index, sf::Joystick::V)};
  }
  /// maps button names to ids
  std::map<ButtonNames, ButtonID> button_map{
      {ButtonNames::A, 0},
      {ButtonNames::B, 1},
      {ButtonNames::X, 2},
      {ButtonNames::Y, 3},

      {ButtonNames::LeftBumper, 4},
      {ButtonNames::RightBumper, 5},
      {ButtonNames::LeftTrigger, 6},
      {ButtonNames::RightTrigger, 7},

      {ButtonNames::Back, 8},
      {ButtonNames::Start, 9},

      {ButtonNames::XBOX, 10},

      {ButtonNames::LeftThumbClick, 11},
      {ButtonNames::RightThumbClick, 12},

      {ButtonNames::DpadLeft, 13},
      {ButtonNames::DpadRight, 14},
      {ButtonNames::DpadUp, 15},
      {ButtonNames::DpadDown, 16},

      {ButtonNames::LeftTriggerValue, 17},
      {ButtonNames::RightTriggerValue, 18},
  };

  /// which gamepad port
  unsigned int sf_joystick_index = 0;
  float thumbstick_threshold = 50.0f;
};

}  // namespace gamelib3
