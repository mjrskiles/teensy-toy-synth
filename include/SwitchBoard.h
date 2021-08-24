/*
 * This utility is intended to track and translate connections
 * between controls and actions
 */

#ifndef SYNTH_SWITCHBOARD_H
#define SYNTH_SWITCHBOARD_H

#include <cstdint>

typedef uint8_t ActionType_t;

enum ActionTypes : ActionType_t {
    ACTION_MIDI_NOTE_INPUT,
};

struct Action {
    ActionType_t actionType;

};

class Switchboard {
public:

};

#endif //SYNTH_SWITCHBOARD_H
