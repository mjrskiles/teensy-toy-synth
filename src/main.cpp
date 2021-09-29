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
elapsedMillis scanTime;
uint8_t lastState = 0;
float asdrScalar = 750.0;

// Interrupt routines
volatile uint8_t lower8NumInterrupts = 0;
volatile uint8_t upper8NumInterrupts = 0;
volatile uint8_t periphNumInterrupts = 0;
void lowerKB_ISR() {
    lower8NumInterrupts++;
}
void upperKB_ISR() {
    upper8NumInterrupts++;
}
void periph_ISR() {
    periphNumInterrupts++;
}

void setup() {
    Serial.begin(9600);
    Serial7.begin(9600);
    Wire.begin();

    pinMode(MCP_RESET_PIN_LOWER_8, OUTPUT);
    pinMode(MCP_LOWER_INTERRUPT_PIN, INPUT_PULLUP);
    delay(300); // Pull up resistors gotta pull up

    digitalWrite(MCP_RESET_PIN_LOWER_8, HIGH);
    pollsterLower8.init();
    pollsterUpper8.init();
    pollsterPeriph.init();
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
    mixerEnv1.gain(0, 0.0);
    mixerEnv1.gain(1, 1.0);

    attachInterrupt(MCP_LOWER_INTERRUPT_PIN, lowerKB_ISR, FALLING);
    attachInterrupt(MCP_UPPER_INTERRUPT_PIN, upperKB_ISR, FALLING);
    attachInterrupt(MCP_PERIPH_INTERRUPT_PIN, periph_ISR, FALLING);
}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
    }

    float knob_Volume = (float)analogRead(KNOB_VOLUME_PIN) / 1023.0f; //volume knob on audio board
    float knob_A = (float)analogRead(KNOB_A_PIN) / 1023.0f;
    float knob_S = (float)analogRead(KNOB_S_PIN) / 1023.0f;
    float knob_D = (float)analogRead(KNOB_D_PIN) / 1023.0f;
    float knob_R = (float)analogRead(KNOB_R_PIN) / 1023.0f;

    sgtl5000_1.volume(knob_Volume);
//
    // Poll the inputs because there was an interrupt
    if(lower8NumInterrupts) {
        Serial.println("Lower 8 INTERRUPT");
        Serial.println(lower8NumInterrupts);
        pollsterLower8.poll();
        lower8NumInterrupts = 0;
    }
    if(upper8NumInterrupts) {
        Serial.println("Upper 8 INTERRUPT");
        Serial.println(upper8NumInterrupts);
        pollsterUpper8.poll();
        upper8NumInterrupts = 0;
    }
    if(periphNumInterrupts) {
        Serial.println("Peripheral I/O INTERRUPT");
        Serial.println(periphNumInterrupts);
        pollsterPeriph.poll();
        periphNumInterrupts = 0;
    }



    if (logPrintoutMillisSince > 500) {
        logr.info("B~ logr v0.1 B~");
        logr.info("Program scan ms:");
        Serial.println(scanTime);
        envelope2.attack(asdrScalar * knob_A);
        envelope2.decay(asdrScalar * knob_D);
        envelope2.sustain(knob_S);
        envelope2.release(asdrScalar * knob_R);
//        Serial.printf(" A  | D  | S  | R\n");
//        Serial.printf("%4.2f %4.2f %4.2f %4.2f\n", knob_A, knob_D, knob_S, knob_R);
        lastState = 0;
        logPrintoutMillisSince = 0;
    }

    scanTime = 0;
}
