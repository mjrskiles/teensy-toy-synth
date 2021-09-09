#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

#include "teensy41pinout.h"
//#include "frequencies.h"
#include "luts.h"
#include "MCP23008.h"
#include "I2C1602.h"

#define DISPLAY_SERIAL Serial1
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


Bounce buttonSelect = Bounce(BUTTON_SELECT_PIN, 15);
const int NUM_BUTTONS = 16;
Bounce button0 =   Bounce(BUTTON_0_PIN, 15);
Bounce button1 =   Bounce(BUTTON_1_PIN, 15);
Bounce button2 =   Bounce(BUTTON_2_PIN, 15);
Bounce button3 =   Bounce(BUTTON_3_PIN, 15);
Bounce button4 =   Bounce(BUTTON_4_PIN, 15);
Bounce button5 =   Bounce(BUTTON_5_PIN, 15);
Bounce button6 =   Bounce(BUTTON_6_PIN, 15);
Bounce button7 =   Bounce(BUTTON_7_PIN, 15);
Bounce button8 =   Bounce(BUTTON_8_PIN, 15);
Bounce button9 =   Bounce(BUTTON_9_PIN, 15);
Bounce button10 =   Bounce(BUTTON_10_PIN, 15);
Bounce button11 =   Bounce(BUTTON_11_PIN, 15);
Bounce button12 =   Bounce(BUTTON_12_PIN, 15);
Bounce button13 =   Bounce(BUTTON_13_PIN, 15);
Bounce button14 =   Bounce(BUTTON_14_PIN, 15);
Bounce button15 =   Bounce(BUTTON_15_PIN, 15);
Bounce *noteButtons[NUM_BUTTONS] = {
        &button0, &button1, &button2, &button3,
        &button4, &button5, &button6, &button7,
        &button8, &button9, &button10, &button11,
        &button12, &button13, &button14, &button15,
};

const char *scaleName = "C Major\0";
Scale scale {
    scaleName, {
        MidiNotes::NOTE_C4, MidiNotes::NOTE_D4, MidiNotes::NOTE_E4, MidiNotes::NOTE_F4,
        MidiNotes::NOTE_G4, MidiNotes::NOTE_A4, MidiNotes::NOTE_B4, MidiNotes::NOTE_C5,
        MidiNotes::NOTE_D5, MidiNotes::NOTE_E5, MidiNotes::NOTE_F5, MidiNotes::NOTE_G5,
        MidiNotes::NOTE_A5, MidiNotes::NOTE_B5, MidiNotes::NOTE_C6, MidiNotes::NOTE_D6
    }
};

const uint8_t hello_buf[] = {'K','i','m',' ','i','s',' ','c','u','t','e'};

int firstPass = 1;
MCP23008 kbLower8;
I2C1602Writer displayWriter(0x27);
lcd16x2 lcd(displayWriter);
// Debugging / Logging
elapsedMillis logPrintoutMillisSince;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(200);
    pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_0_PIN, INPUT_PULLUP);
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(BUTTON_3_PIN, INPUT_PULLUP);
    pinMode(BUTTON_4_PIN, INPUT_PULLUP);
    pinMode(BUTTON_5_PIN, INPUT_PULLUP);
    pinMode(BUTTON_6_PIN, INPUT_PULLUP);
    pinMode(BUTTON_7_PIN, INPUT_PULLUP);

    delay(300); // Pull up resistors gotta pull up

    // lcd16x2 should be  good to go after 500ms
//    lcd.displayOn();

//    delay(500);
//    lcd.clearDisplay();
    lcd.writeBytes(hello_buf, 11);
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

//    DISPLAY_SERIAL.print("Hello World!");
}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
    }
    uint8_t gpio = kbLower8.readRegister(0x09); // check the io register

    // TODO grab a button handle out of the array instead
    // Read the buttons and knobs, scale knobs to 0-1.0
    buttonSelect.update();
    button0.update();
    button1.update();
    button2.update();
    button3.update();
    button4.update();
    button5.update();
    button6.update();
    button7.update();
    button8.update();
    button9.update();
    button10.update();
    button11.update();
    button12.update();
    button13.update();
    button14.update();
    button15.update();


//    for (int i = 0; i < NUM_BUTTONS; i++) {
//        Bounce button = *(noteButtons[i]);
//        button.update();
//    }

    float knob_A1 = (float)analogRead(15) / 1023.0f; //volume knob on audio board
    float knob_A2 = (float)analogRead(KNOB_1_PIN) / 1023.0f;
    float knob_A3 = (float)analogRead(KNOB_2_PIN) / 1023.0f;

    sgtl5000_1.volume(knob_A1);
    phaseCtrl1.frequency(knob_A2);
    lpfCtrl.frequency(knob_A3);

    if (logPrintoutMillisSince > 1000) {
            Serial.printf("MCP GPIO reg: 0x%02x\n", (unsigned int) ~(gpio & 0xFF));
            logPrintoutMillisSince = 0;
    }

    if (button0.fallingEdge()) {
        Serial.println("Button 0 direct ref test");
    }

    for (int i = 0; i < NUM_BUTTONS; i++) {
        Bounce button = *(noteButtons[i]);

        // Button is pressed
        if (button.fallingEdge()) {
            Serial.printf("button %n fall\n", i);
            squarewaveBase.frequency(scale.ButtonMap[i]);
            squarewaveBase.amplitude(1.0f);

            squarewavePhaseMod.frequency(scale.ButtonMap[i]);
            squarewavePhaseMod.amplitude(1.0f);
        }

        // Released
        if (button.risingEdge()) {
            Serial.printf("button %n rise\n", i);
            squarewaveBase.amplitude(0.0f);
            squarewavePhaseMod.amplitude(0.0f);
        }
    }

    // Button select changes the waveform type
    if (buttonSelect.fallingEdge()) {
        Serial.println("Log Button");
        Serial.println("Control  | Value");
        Serial.printf( "Knob 1     %.2f\n", knob_A1);
        Serial.printf( "Knob 2     %.2f\n", knob_A2);
        Serial.printf( "Knob 3     %.2f\n", knob_A3);
        logPrintoutMillisSince = 0;
    }
  
}
