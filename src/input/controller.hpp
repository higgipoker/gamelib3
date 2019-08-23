#pragma once
#include <array>
#include <iostream>
#include <vector>
namespace gamelib3 {

/**
 * @brief The InputState enum
 */
enum class InputState {
  // dpad
  Up = 0,
  Down,
  Left,
  Right,

  // button 1
  FireDown,
  FireUp,
  FireLength,
  FireLengthCached,
  SingleTap,
  DoubleTap,
  FirePress,

  // button 2
  FireDown2,
  FireUp2,
  FireLength2,
  FireLengthCached2,
  SingleTap2,
  DoubleTap2,
  FirePress2,

  // button 3
  FireDown3,
  FireUp3,
  FireLength3,
  FireLengthCached3,
  SingleTap3,
  DoubleTap3,
  FirePress3,

  // button 4
  FireDown4,
  FireUp4,
  FireLength4,
  FireLengthCached4,
  SingleTap4,
  DoubleTap4,
  FirePress4,

  InputStates
};

/**
 * @brief The ControllerEventID enum
 */
enum class ControllerEventID {
  NoEvent = 0,
  Fire,
  FireTap,
  DPadLeft,
  DPadRight,
  DPadUp,
  DPadDown
};

/**
 * @brief The ControllerEventStatus enum
 */
enum class ControllerEventStatus { Released = 0, Pressed };

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
  /**
   * @brief ControllerEvent
   */
  ControllerEvent() {
    id = ControllerEventID::NoEvent;
    status = ControllerEventStatus::Released;
    param = 0;
  }

  /**
   * @brief ControllerEvent
   * @param i
   * @param s
   * @param p
   */
  ControllerEvent(ControllerEventID i, ControllerEventStatus s, int p = 0) {
    id = i;
    status = s;
    param = p;
  }

  ControllerEventID id;
  ControllerEventStatus status;
  int param;
};

/**
 * @brief The ControllerListener class
 */
class ControllerListener {
 public:
  /**
   * @brief OnControllerEvent
   * @param event
   */
  virtual void OnControllerEvent(const ControllerEvent &event) = 0;
};

class Controller {
 public:
  /**
   * @brief Controller
   */
  Controller();

  /**
   * @brief Poll
   */
  void Poll();

  /**
   * @brief AddListener
   * @param listener
   */
  void AddListener(ControllerListener* listener);

  /**
   * @brief Log
   */
  inline void Log() {
    std::cout << "Fire 1: " << states[static_cast<size_t>(InputState::FireDown)]
              << std::endl;
    std::cout << "Fire 2: "
              << states[static_cast<size_t>(InputState::FireDown2)]
              << std::endl;

    std::cout << "Left: " << states[static_cast<size_t>(InputState::Left)]
              << std::endl;
    std::cout << "Right: " << states[static_cast<size_t>(InputState::Right)]
              << std::endl;
    std::cout << "Down: " << states[static_cast<size_t>(InputState::Down)]
              << std::endl;
    std::cout << "Up: " << states[static_cast<size_t>(InputState::Up)]
              << std::endl;
  }

  std::array<int, static_cast<size_t>(InputState::InputStates)> states{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

 protected:
  /**
   * @brief on_poll
   */
  virtual void on_poll() = 0;

  /**
   * @brief notify
   */
  void notify(ControllerEvent event);
  std::vector<ControllerListener *> listeners;
  /// count fire ticks
  std::array<int, 4> fire_ticks{0, 0, 0, 0};
  /// how fast is a tap
  static const int fire_tap_length = 5;
};
}  // namespace gamelib3
