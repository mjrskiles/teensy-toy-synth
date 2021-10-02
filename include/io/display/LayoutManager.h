//
// Created by Michael Skiles on 9/30/21.
//

#ifndef TEENSY_SYNTH_LAYOUTMANAGER_H
#define TEENSY_SYNTH_LAYOUTMANAGER_H

#include "../../../lib/LCD16x2/lcd16x2.h"
#include "Layout.h"


/*
 * I want this class to be able to handle the business logic of updating the lcd
 * with relevant data
 *
 * it should be able to play back animations stored in a topBuffer
 *
 * it should have some way to register a data layout and update it
 *
 */
class LayoutManager {
public:
    LayoutManager(lcd16x2 &lcd, const Layout &currentLayout);

    void startCyclicUpdate();
    void update();
    void setLayout(Layout &layout);
    void runLayout();
    void stopLayout();
private:
    bool _runLayoutFlag = false;
    lcd16x2& _lcd;
    Layout _currentLayout;
    elapsedMillis _updateTicker;
};

#endif //TEENSY_SYNTH_LAYOUTMANAGER_H
