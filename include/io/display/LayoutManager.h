//
// Created by Michael Skiles on 9/30/21.
//

#ifndef TEENSY_SYNTH_LAYOUTMANAGER_H
#define TEENSY_SYNTH_LAYOUTMANAGER_H

#include "lcd16x2.h"
#include "Layout.h"


/*
 * I want this class to be able to handle the business logic of updating the lcd
 * with relevant data
 *
 * it should be able to play back animations stored in a buffer
 *
 * it should have some way to register a data layout and update it
 *
 */
#define NUM_LAYOUTS 3

class LayoutManager {
public:
    LayoutManager(lcd16x2 &lcd, const Layout &currentLayout, Layout *layouts);

    void startCyclicUpdate();
    void update();
    void setLayout(Layout &layout);
    void nextLayout();
    void previousLayout();
    void runLayout();
    void stopLayout();
private:
    bool _runLayoutFlag = false;
    lcd16x2& _lcd;
    Layout _currentLayout;
    uint8_t _currentLayoutIndex = 0;
    Layout *_layouts;
    elapsedMillis _updateTicker;
};

#endif //TEENSY_SYNTH_LAYOUTMANAGER_H
