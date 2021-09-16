#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

#include "teensy41pinout.h"
#include "luts.h"
#include "MCP23008.h"
#include "lcd16x2.h"
#include "Controller.h"
#include "InputControllers.h"

#define DISPLAY_I2C Wire

// GUItool: begin automatically generated code
AudioSynthWaveform       squarewaveBase;      //xy=90,59
AudioSynthWaveformSine   phaseCtrl1;          //xy=99,237
AudioSynthWaveformModulated squarewavePhaseMod;   //xy=260,303
AudioEffectEnvelope      envelope2;      //xy=294,119
AudioEffectEnvelope      envelope1;      //xy=381,396
AudioMixer4              mixerEnv1;         //xy=482,113
AudioMixer4              mixerEnv2;         //xy=482,293
AudioMixer4              oscCombineMixer;         //xy=613,187
AudioSynthWaveformSine   lpfCtrl;          //xy=645,300
AudioFilterStateVariable lpf1;        //xy=781,191
AudioMixer4              mixer1;         //xy=984,193
AudioOutputI2S           i2s1;           //xy=1149,189
AudioConnection          patchCord1(squarewaveBase, envelope2);
AudioConnection          patchCord2(squarewaveBase, 0, mixerEnv1, 0);
AudioConnection          patchCord3(phaseCtrl1, 0, squarewavePhaseMod, 0);
AudioConnection          patchCord4(squarewavePhaseMod, envelope1);
AudioConnection          patchCord5(squarewavePhaseMod, 0, mixerEnv2, 0);
AudioConnection          patchCord6(envelope2, 0, mixerEnv1, 1);
AudioConnection          patchCord7(envelope1, 0, mixerEnv2, 1);
AudioConnection          patchCord8(mixerEnv1, 0, oscCombineMixer, 0);
AudioConnection          patchCord9(mixerEnv2, 0, oscCombineMixer, 1);
AudioConnection          patchCord10(oscCombineMixer, 0, lpf1, 0);
AudioConnection          patchCord11(lpfCtrl, 0, lpf1, 1);
AudioConnection          patchCord12(lpf1, 0, mixer1, 0);
AudioConnection          patchCord13(mixer1, 0, i2s1, 0);
AudioConnection          patchCord14(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=585,481
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

const char *nametest = "note0!";

// the callbacks are defined in inputcontrollers.h
extern void (*listener_callback)(InputSnapshot) = &noteButtonListenerCallback;
extern void* (*pollCallback)() = &note0PollsterCallback;
extern void (*initCallback)() = &pollsterInit;

InputListener note0Listeners[] = {
        InputListener(listener_callback,
                      nametest)
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

    delay(300); // Pull up resistors gotta pull up
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

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(24);

    // Comment these out if not using the audio adaptor board.
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);

    // Configure for middle C note without modulation
    squarewaveBase.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.phaseModulation(360.0f);
    phaseCtrl1.frequency(500.0f);
    lpfCtrl.frequency(20000.0f);

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
    sgtl5000_1.volume(knob_A1);
    phaseCtrl1.frequency(knob_A2);
    lpfCtrl.frequency(knob_A3);

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

    // Button select changes the waveform type
    if (false) {
        Serial.println("Log Button");
        Serial.println("Control  | Value");
        Serial.printf( "Knob 1     %.2f\n", knob_A1);
        Serial.printf( "Knob 2     %.2f\n", knob_A2);
        Serial.printf( "Knob 3     %.2f\n", knob_A3);
        logPrintoutMillisSince = 0;
    }
  
}
