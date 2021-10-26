#include <Audio.h>
#include <Wire.h>
#include <Bounce.h>

#include "model/teensy41pinout.h"
#include "io/display/lcd16x2.h"
#include "synthesizer/components.h"
#include "Logr.h"
#include <synthesizer/pwm_synth.h>
#include <MIDI.h>

#define DISPLAY_I2C Wire

const char *hello_buf = "Kim is so cute";

PwmSynth pwmSynth = PwmSynth();
SerialLCDWriter displayWriter = SerialLCDWriter();
lcd16x2 lcd(displayWriter);
LayoutManager layoutManager = LayoutManager(lcd, layout_noteIO, layouts);

// MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial6, MIDI);
volatile int noteOnCounter = 0;
void handleNoteOn(byte channel, byte pitch, byte velocity) {
    pwmSynth.noteOn(MidiNote(pitch), 127);
    noteOnCounter++;
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
    pwmSynth.noteOff(MidiNote(pitch));
}

// Debugging / Logging
Logr logr = Logr();
int firstPass = 1;
elapsedMillis logPrintoutMillisSince;
elapsedMicros scanTime;
uint8_t lastState = 0;
float adsrScalarMs = 750.0; //in milliseconds

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

// Rotary encoder for 16x2 LCD
#define NO_CHANGE 0
#define NEXT_PAGE 1
elapsedMillis pageChangeDebounce = 0;
volatile uint8_t encoderCommandWord = 0;
void encoderAPinLow_ISR() {
    encoderCommandWord = NEXT_PAGE;
}




void setup() {
    Serial.begin(9600);
    Serial7.begin(9600);
    MIDI.begin(1);
    while(!Serial && !Serial7);
    Wire.begin();
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    AudioMemory(96);

    pinMode(MCP_RESET_PIN, OUTPUT);
    pinMode(MCP_LOWER_INTERRUPT_PIN, INPUT_PULLUP);
    pinMode(ENCODER1_A_PIN, INPUT);
    pinMode(PLAY_STEP_BUTTON_PIN, INPUT);
    pinMode(RECORD_BUTTON_PIN, INPUT);
    digitalWrite(MCP_RESET_PIN, LOW);
    delay(500); // Pull up resistors gotta pull up, let everything power up

    attachInterrupt(MCP_LOWER_INTERRUPT_PIN, lowerKB_ISR, FALLING);
    attachInterrupt(MCP_UPPER_INTERRUPT_PIN, upperKB_ISR, FALLING);
    attachInterrupt(MCP_PERIPH_INTERRUPT_PIN, periph_ISR, FALLING);
    attachInterrupt(ENCODER1_A_PIN, encoderAPinLow_ISR, FALLING);

//    toySynth.synth_init();
//    mixerEnv1.gain(0, 0.0);
//    mixerEnv1.gain(1, 1.0);
    pwmSynth.init();

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
    MIDI.read();

    if (firstPass) {
        firstPass = 0;
        Serial.println("First Pass");
        layoutManager.startCyclicUpdate();
        layoutManager.runLayout();
    }
//    pwmSynth.update();


    attackValueRaw = analogRead(KNOB_A_PIN);
    decayValueRaw = analogRead(KNOB_D_PIN);
    sustainValueRaw = analogRead(KNOB_S_PIN);
    releaseValueRaw = analogRead(KNOB_R_PIN);

    knobVolumeScaled = (float)analogRead(KNOB_VOLUME_PIN) / 1023.0f; //volume knob on audio board
    analog_control_1 = 1 - ((float)attackValueRaw / 1023.0f);
    analog_control_2 = 1 - ((float)decayValueRaw / 1023.0);
    analog_control_3 = 1 - ((float)sustainValueRaw /  1023.0);
    analog_control_4 = 1 - ((float)releaseValueRaw /  1023.0);

    pwmSynth.controlChange(0, analog_control_1);
    pwmSynth.controlChange(1, analog_control_2);
    pwmSynth.controlChange(2, analog_control_3);
    pwmSynth.controlChange(3, analog_control_4);

    sgtl5000_1.volume(knobVolumeScaled);

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

    if (pageChangeDebounce > 100 && encoderCommandWord == NEXT_PAGE) {
        layoutManager.nextLayout();
        pageChangeDebounce = 0;
    }
    encoderCommandWord = NO_CHANGE;

    layoutManager.update();

    // Logging
    if (digitalRead(RECORD_BUTTON_PIN) == LOW && logPrintoutMillisSince > 100) {
        logr.info("Program scan us:");
        Serial.println(scanTime);
        uint8_t lower_state = mcp_kbLower8.readRegister(mcp_kbLower8.getGpio());
        uint8_t upper_state = mcp_kbUpper8.readRegister(mcp_kbUpper8.getGpio());
        Serial.printf("Keyboard IO word: 0x%x\n", keyboard_io_word);
        Serial.printf("Keyboard actual lower: 0x%x\n", lower_state);
        Serial.printf("Keyboard actual upper: 0x%x\n", upper_state);

        Serial.printf("Midi note on counter: %d\n", noteOnCounter);

        Serial.printf(" 1  | 2  | 3  | 4\n");
        Serial.printf("%4.2f %4.2f %4.2f %4.2f\n", analog_control_1, analog_control_2, analog_control_3, analog_control_4);
        lastState = 0;
        logPrintoutMillisSince = 0;
    }

    scanTime = 0;
}
