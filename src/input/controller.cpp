#include "controller.hpp"

namespace gamelib3 {
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
Controller::Controller() {}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Controller::Poll() {
  // for comparison for events (chaged statuses)
  std::array<int, static_cast<size_t>(InputState::InputStates)> old_states =
      states;

  on_poll();

  //
  // Fire event
  //
  if (old_states[static_cast<size_t>(InputState::FireDown)]) {
    if (states[static_cast<size_t>(InputState::FireUp)]) {
      if (states[static_cast<size_t>(InputState::FireLengthCached)] <
          fire_tap_length) {
        notify(ControllerEvent(ControllerEventID::FireTap,
                               ControllerEventStatus::Released));
        std::cout << "fire tap" << std::endl;
      } else {
        notify(ControllerEvent(
            ControllerEventID::Fire, ControllerEventStatus::Released,
            states[static_cast<size_t>(InputState::FireLengthCached)]));
        std::cout << "fire up" << std::endl;
      }
    }

  } else {
    if (states[static_cast<size_t>(InputState::FireDown)]) {
      notify(ControllerEvent(ControllerEventID::Fire,
                             ControllerEventStatus::Pressed));
      std::cout << "fire down" << std::endl;
    }
  }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void Controller::notify(ControllerEvent event) {
  for (auto &listener : listeners) {
    listener->OnControllerEvent(event);
  }
}
}  // namespace gamelib3
