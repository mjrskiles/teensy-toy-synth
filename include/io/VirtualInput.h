//
// Created by Michael Skiles on 9/22/21.
//

#ifndef SYNTH_VIRTUALINPUT_H
#define SYNTH_VIRTUALINPUT_H


#include "InputListener.h"

class VirtualInput {
public:
    VirtualInput(InputListener *inputListeners, uint8_t currentSize, int index, InputDataType inputDataType);

    int getIndex() const;

    String toString();
    void addListener(InputListener listener);
    void notifyChangeListeners();
private:
    InputListener *_inputListeners;
    uint8_t _currentSize = 0;
    int _index = 0;
    InputDataType _inputDataType = BOOL;
};

#endif //SYNTH_VIRTUALINPUT_H
