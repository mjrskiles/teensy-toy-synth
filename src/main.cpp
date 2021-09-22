#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

#include "teensy41pinout.h"
#include "luts.h"
#include "io/MCP23008.h"
#include "lcd16x2.h"
#include "io/Controller.h"
#include "io/InputControllers.h"
#include "synthesizer/synthesizer.h"
#include "io/toyIO.h"

#define DISPLAY_I2C Wire

// GUItool: begin automatically generated code
   //xy=585,481
// GUItool: end automatically generated code

const char *scaleName = "C Major\0";
Scale scale {
    scaleName, {
        MidiNotes::NOTE_C4, MidiNotes::NOTE_D4, MidiNotes::NOTE_E4, MidiNotes::NOTE_F4,
        MidiNotes::NOTE_G4, MidiNotes::NOTE_A4, MidiNotes::NOTE_B4, MidiNotes::NOTE_C5,
        MidiNotes::NOTE_D5, MidiNotes::NOTE_E5, MidiNotes::NOTE_F5, MidiNotes::NOTE_G5,
        MidiNotes::NOTE_A5, MidiNotes::NOTE_B5, MidiNotes::NOTE_C6, MidiNotes::NOTE_D6
    }
};

const char *hello_buf = "Kim is so cute";

int firstPass = 1;
MCP23008 kbLower8;
SerialLCDWriter displayWriter = SerialLCDWriter();
lcd16x2 lcd(displayWriter);
// Debugging / Logging
elapsedMillis logPrintoutMillisSince;
uint8_t lastState = 0;


// the callbacks are defined in inputcontrollers.h
void (*listener_callback)(InputSnapshot&) = &noteButtonListenerCallback;
void* (*pollCallback)() = &note0PollsterCallback;
void (*initCallback)() = &pollsterInit;

InputListener note0Listeners[] = {
        InputListener(listener_callback,
                      "note0")
};
VirtualInput note0 = VirtualInput(note0Listeners);
VirtualInput mcpUpper8VirtualInputs[] = {
        note0
};
InputPollster pollsterUpper8 = InputPollster(pollCallback,
                                             initCallback, mcpUpper8VirtualInputs);

void setup() {
    Serial.begin(9600);
    Serial7.begin(9600);
    Wire.begin();
    pinMode(MCP_RESET_PIN_LOWER_8, OUTPUT);
    delay(300); // Pull up resistors gotta pull up
    digitalWrite(MCP_RESET_PIN_LOWER_8, HIGH);
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

    synth_init();

    Serial.println("Begin mcp init block");
    kbLower8 = MCP23008(0x22);
    Serial.println("constructor");
    kbLower8.init();
    Serial.println("init");
    delay(100);
    uint8_t iocon = kbLower8.readRegister(0x05); // check the iocon register
    Serial.println("iocon read");
    Serial.printf("MCP IOCON reg: %hhu\n", iocon);
    uint8_t gppu = kbLower8.readRegister(0x06);
    Serial.printf("MCP GPPU reg: %hhu\n", gppu);
    Serial.println("End mcp init block");

}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
    }

    float knob_A1 = (float)analogRead(15) / 1023.0f; //volume knob on audio board
    float knob_A2 = (float)analogRead(KNOB_1_PIN) / 1023.0f;
    float knob_A3 = (float)analogRead(KNOB_2_PIN) / 1023.0f;
//    sgtl5000_1.volume(knob_A1);
//    phaseCtrl1.frequency(knob_A2);
//    lpfCtrl.frequency(knob_A3);

    uint8_t gpio = kbLower8.readRegister(0x09); // check the io register

    if (logPrintoutMillisSince > 500) {
        pollsterUpper8.poll();
        if (gpio != lastState) {
            Serial.printf("--MCP GPIO reg: 0x%02x\n", (unsigned int) gpio);
            size_t written = 0;
//            written = lcd.writeByte(0x47);
//            Serial.println("lcd16x2::writeBytes wrote bytes!");
            lcd.writeByte(0xfe);
            lcd.writeByte(0x80);
            lcd.writeByte((uint8_t)'h');
            lcd.writeByte((uint8_t)'e');
            lcd.writeByte((uint8_t)'l');
            lcd.writeByte((uint8_t)'l');
            lcd.writeByte((uint8_t)'0');
            Serial.println((int)written);
            lastState = gpio;
        }
        logPrintoutMillisSince = 0;
    }

  
}
