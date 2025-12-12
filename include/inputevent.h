#ifndef H_CARL_INPUTEVENT
#define H_CARL_INPUTEVENT
#include <stdint.h>

/// The type of the input
enum InputType {
  InputBeatButton = 0, ///< one of the main 8 pattern buttons
  InputMove = 1, ///< the "arrow" keys
  InputMod = 2, ///< the modifier key
};

typedef struct input_event {
  InputType type;
  uint32_t data;
} InputEvent;

#endif // !H_CARL_INPUTEVENT
