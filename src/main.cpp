#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>
#include <synthesizer/synthesizer.h>

#include "teensy41pinout.h"
#include "io/MCP23008.h"
#include "lcd16x2.h"
#include "synthesizer/components.h"
#include "Logr.h"


#define DISPLAY_I2C Wire

const char *hello_buf = "Kim is so cute";

ToySynth toySynth;
Logr logr = Logr();
int firstPass = 1;
SerialLCDWriter displayWriter = SerialLCDWriter();
lcd16x2 lcd(displayWriter);
// Debugging / Logging
elapsedMillis logPrintoutMillisSince;
uint8_t lastState = 0;

uint16_t buttonWordBuffer = 0;

void updateInputsFromBuffer() {


    uint16_t buttonStateWordLast = buttonWordBuffer;
    buttonWordBuffer = 0;
    for (int i = 0; i < 15; i++) {
        InputSnapshotBool snapshot = INPUT_BUFFER_BOOL[i];
        buttonWordBuffer |= snapshot.asBool() ? (1 << i) : 0;
    }//TODO no magic numbers, this is for testing

    if (buttonWordBuffer != 0) {
        for (int i = 0; i < 15; i++) {
            Serial.printf("%s ", (buttonWordBuffer & (1 <<i)) ? "true" : "false");
        }
    }
}

void setup() {
    Serial.begin(9600);
    Serial7.begin(9600);
    Wire.begin();
    pinMode(MCP_RESET_PIN_LOWER_8, OUTPUT);
    delay(300); // Pull up resistors gotta pull up
    digitalWrite(MCP_RESET_PIN_LOWER_8, HIGH);
    pollsterLower8.init();
    pollsterUpper8.init();
    // lcd16x2 should be  good to go after 500ms
    lcd.displayOff();
    lcd.clearDisplay();
    lcd.displayOn();
    lcd.writeByte(0xfe);
    lcd.writeByte(0x80);
    lcd.writeByte((uint8_t)'i');
    lcd.writeByte((uint8_t)'n');
    lcd.writeByte((uint8_t)'i');
    lcd.writeByte((uint8_t)'t');

    toySynth.synth_init();

}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
    }

    float knob_A1 = (float)analogRead(15) / 1023.0f; //volume knob on audio board
    float knob_A2 = (float)analogRead(KNOB_1_PIN) / 1023.0f;
    float knob_A3 = (float)analogRead(KNOB_2_PIN) / 1023.0f;
    pollsterUpper8.poll();
    pollsterLower8.poll();
    pollsterPeriph.poll();
//    updateInputsFromBuffer();

    if (logPrintoutMillisSince > 500) {

        lastState = 0;
        logPrintoutMillisSince = 0;
    }

  
}
