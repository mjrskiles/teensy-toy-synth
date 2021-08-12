#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

#include "teensy41pinout.h"
#include "frequencies.h"

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
Bounce button1 = Bounce(BUTTON_1_PIN, 15);
Bounce button2 = Bounce(BUTTON_2_PIN, 15);
Bounce button3 = Bounce(BUTTON_3_PIN, 15);
Bounce button4 = Bounce(BUTTON_4_PIN, 15);
Bounce button5 = Bounce(BUTTON_5_PIN, 15);
Bounce button6 = Bounce(BUTTON_6_PIN, 15);
Bounce button7 = Bounce(BUTTON_7_PIN, 15);
Bounce button8 = Bounce(BUTTON_8_PIN, 15);

int current_waveform=0;
int firstPass = 1;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_1_PIN, INPUT_PULLUP);
    pinMode(BUTTON_2_PIN, INPUT_PULLUP);
    pinMode(BUTTON_3_PIN, INPUT_PULLUP);
    pinMode(BUTTON_4_PIN, INPUT_PULLUP);
    pinMode(BUTTON_5_PIN, INPUT_PULLUP);
    pinMode(BUTTON_6_PIN, INPUT_PULLUP);
    pinMode(BUTTON_7_PIN, INPUT_PULLUP);
    pinMode(BUTTON_8_PIN, INPUT_PULLUP);


    delay(300);
    Serial.println("Waveform Modulation Test");
  
    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(24);

    // Comment these out if not using the audio adaptor board.
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5); // caution: very loud - use oscilloscope only!

    // Configure for middle C note without modulation
    squarewaveBase.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.begin(WAVEFORM_SQUARE);
    squarewavePhaseMod.phaseModulation(360.0f);
    phaseCtrl1.frequency(20.3f);
    lpfCtrl.frequency(5000.0f);
}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
    }
    // Read the buttons and knobs, scale knobs to 0-1.0
    buttonSelect.update();
    button1.update();
    button2.update();
    button3.update();
    button4.update();
    button5.update();
    button6.update();
    button7.update();
    button8.update();
    float knob_A1 = (float)analogRead(15) / 1023.0f; //volume knob on audio board
    float knob_A2 = (float)analogRead(KNOB_1_PIN) / 1023.0f;
    float knob_A3 = (float)analogRead(KNOB_2_PIN) / 1023.0f;

    sgtl5000_1.volume(knob_A1);
    phaseCtrl1.frequency(knob_A2);
    lpfCtrl.frequency(knob_A3);

    if (button1.fallingEdge()) {
        Serial.println("button1f");
        Serial.println("Knob 1 value:");
        Serial.println(knob_A1);
        Serial.println("Knob 2 value:");
        Serial.println(knob_A2);
        Serial.println("Knob 3 value:");
        Serial.println(knob_A3);
        squarewaveBase.frequency(C4);
        squarewaveBase.amplitude(1.0f);

        squarewavePhaseMod.frequency(C4);
        squarewavePhaseMod.amplitude(1.0f);
    }

    if (button1.risingEdge()) {
        Serial.println("button1r");
        squarewaveBase.amplitude(0.0f);
        squarewavePhaseMod.amplitude(0.0f);
    }

    if (button2.fallingEdge()) {
        Serial.println("button2f");
        squarewaveBase.frequency(D4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button2.risingEdge()) {
        Serial.println("button2r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button3.fallingEdge()) {
        Serial.println("button3f");
        squarewaveBase.frequency(E4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button3.risingEdge()) {
        Serial.println("button3r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button4.fallingEdge()) {
        Serial.println("button4f");
        squarewaveBase.frequency(F4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button4.risingEdge()) {
        Serial.println("button4r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button5.fallingEdge()) {
        Serial.println("button5f");
        squarewaveBase.frequency(G4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button5.risingEdge()) {
        Serial.println("button5r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button6.fallingEdge()) {
        Serial.println("button6f");
        squarewaveBase.frequency(A4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button6.risingEdge()) {
        Serial.println("button6r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button7.fallingEdge()) {
        Serial.println("button7f");
        squarewaveBase.frequency(B4);
        squarewaveBase.amplitude(1.0f);
    }
    if (button7.risingEdge()) {
        Serial.println("button7r");
        squarewaveBase.amplitude(0.0f);
    }

    if (button8.fallingEdge()) {
        Serial.println("button8f");
        squarewaveBase.frequency(C5);
        squarewaveBase.amplitude(1.0f);
    }
    if (button8.risingEdge()) {
        Serial.println("button8r");
        squarewaveBase.amplitude(0.0f);
    }

    // Button select changes the waveform type
    if (buttonSelect.fallingEdge()) {
        Serial.println("Button: Select");
    }
  
}
