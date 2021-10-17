#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>
#include <synthesizer/synthesizer.h>

#include "buffers/teensy41pinout.h"
#include "io/MCP23008.h"
#include "io/display/lcd16x2.h"
#include "synthesizer/components.h"
#include "Logr.h"
#include <USB-MIDI.h>
#include "synthesizer/midi_callbacks.h"

#define DISPLAY_I2C Wire

const char *hello_buf = "Kim is so cute";

ToySynth toySynth = ToySynth();
SerialLCDWriter displayWriter = SerialLCDWriter();
lcd16x2 lcd(displayWriter);
LayoutManager testLayoutManager = LayoutManager(lcd, layout_noteIO);

// Debugging / Logging
Logr logr = Logr();
int firstPass = 1;
elapsedMillis logPrintoutMillisSince;
elapsedMicros scanTime;
uint8_t lastState = 0;
float asdrScalar = 750.0;

// Interrupt routines
elapsedMicros lowerDebounce;
elapsedMicros upperDebounce;
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
    while(!Serial && !Serial7);
    Wire.begin();
    usbMIDI.begin();
    usbMIDI.setHandleNoteOn(cb_handleNoteOn);
    usbMIDI.setHandleNoteOff(cb_handleNoteoff);
    AudioMemory(48);

    pinMode(MCP_RESET_PIN, OUTPUT);
    pinMode(MCP_LOWER_INTERRUPT_PIN, INPUT_PULLUP);
    pinMode(PLAY_STEP_BUTTON_PIN, INPUT);
    pinMode(RECORD_BUTTON_PIN, INPUT);
    digitalWrite(MCP_RESET_PIN, LOW);
    delay(500); // Pull up resistors gotta pull up, let everything power up

    attachInterrupt(MCP_LOWER_INTERRUPT_PIN, lowerKB_ISR, FALLING);
    attachInterrupt(MCP_UPPER_INTERRUPT_PIN, upperKB_ISR, FALLING);
    attachInterrupt(MCP_PERIPH_INTERRUPT_PIN, periph_ISR, FALLING);

    toySynth.synth_init();
    mixerEnv1.gain(0, 0.0);
    mixerEnv1.gain(1, 1.0);

    digitalWrite(MCP_RESET_PIN, HIGH);
    pollsterLower8.init();
    pollsterUpper8.init();
    pollsterPeriph.init();

    // lcd16x2 should be  good to go after 500ms
    lcd.displayOff();
    lcd.clearDisplay();
    lcd.displayOn();
    lcd.writeByte(0xfe);
    lcd.writeByte(0x80);

    lcd.userSplash();

    // Don't start the main loop until the play button is pressed
    // This is a good time to attach the serial monitor
    Serial.println("Press the play/step button to start the program");
    while(1) {
        if (digitalRead(PLAY_STEP_BUTTON_PIN) == LOW) { // LOW is pressed
            logr.info("Loop Triggered by Play/step button");
            break;
        }
    }
    logr.info("B~ logr v0.1 B~");
    logr.info("Setup done");
}

void loop() {
    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
        testLayoutManager.startCyclicUpdate();
        testLayoutManager.runLayout();
    }

    float knob_Volume = (float)analogRead(KNOB_VOLUME_PIN) / 1023.0f; //volume knob on audio board
    float knob_A = (float)analogRead(KNOB_A_PIN) / 1023.0f;
    float knob_S = (float)analogRead(KNOB_S_PIN) / 1023.0f;
    float knob_D = (float)analogRead(KNOB_D_PIN) / 1023.0f;
    float knob_R = (float)analogRead(KNOB_R_PIN) / 1023.0f;

    waveform1Envelope.attack(asdrScalar * (1 - knob_A));
    waveform1Envelope.decay(asdrScalar * (1 - knob_D));
    waveform1Envelope.sustain(1 - knob_S);
    waveform1Envelope.release(asdrScalar * (1 - knob_R));

    sgtl5000_1.volume(knob_Volume);

    // This clears the interrupt in case it gets stuck on. There is probably a more logical way to do this.
    // The MCP interrupts don't get cleared till either INTCAP or GPIO register is read. If the callback read fails
    // for any reason the interrupt will get stuck on. This is basically a watchdog for that.
    if (lower8NumInterrupts == 0 && digitalRead(MCP_LOWER_INTERRUPT_PIN) == LOW) {
        mcp_kbLower8.readRegister(mcp_kbLower8.getIntcap());
    }
    if (upper8NumInterrupts == 0 && digitalRead(MCP_UPPER_INTERRUPT_PIN) == LOW) {
        mcp_kbUpper8.readRegister(mcp_kbUpper8.getIntcap());
    }
    if (periphNumInterrupts == 0 && digitalRead(MCP_PERIPH_INTERRUPT_PIN) == LOW) {
        mcp_periph1.readRegister(mcp_periph1.getIntcap());
    }

    // Poll the inputs because there was an interrupt
    if(lower8NumInterrupts) {
        Serial.println("Lower 8 INTERRUPT");
        Serial.println(lower8NumInterrupts);
        pollsterLower8.poll();
        lower8NumInterrupts = 0;
    }
    if(upper8NumInterrupts || digitalRead(MCP_UPPER_INTERRUPT_PIN) == LOW) {
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

    testLayoutManager.update();

    // Logging
    if (digitalRead(RECORD_BUTTON_PIN) == LOW && logPrintoutMillisSince > 100) {
        logr.info("Program scan us:");
        Serial.println(scanTime);
        uint8_t lower_state = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
        uint8_t upper_state = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
        Serial.printf("Keyboard IO word: 0x%x\n", keyboard_io_word);
        Serial.printf("Keyboard actual lower: 0x%x\n", lower_state);
        Serial.printf("Keyboard actual upper: 0x%x\n", upper_state);



//        Serial.printf(" A  | D  | S  | R\n");
//        Serial.printf("%4.2f %4.2f %4.2f %4.2f\n", knob_A, knob_D, knob_S, knob_R);
        lastState = 0;
        logPrintoutMillisSince = 0;
    }

    scanTime = 0;
}
