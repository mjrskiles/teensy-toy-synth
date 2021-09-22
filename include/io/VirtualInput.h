//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_VIRTUALINPUT_H
#define SYNTH_VIRTUALINPUT_H

#include "io/InputSnapshot.h"

class VirtualInput {
public:
    explicit VirtualInput(InputListener *listenersArray);

    VirtualInput(InputListener *inputListeners, uint8_t currentSize, int index, InputDataType inputDataType);

    String toString();
    void addListener(InputListener listener);
protected:
    void notifyChangeListeners();
private:
    InputListener *_inputListeners;
    uint8_t _currentSize = 0;
    int _index = 0;
    InputDataType _inputDataType = BOOL;
};

#endif //SYNTH_VIRTUALINPUT_H
