# toy synth

## useful commands and stuff
`pio init --ide clion`

- reloads project settings after adding a new library
- use it if your syntax highlighting isn't picking up the new lib!

`pio -c clion device monitor -e teensy41`

- open the serial monitor
- TODO does it need the clion part?

## Building

`pio run`

- build the project

`pio run --target upload`

- build the project and upload it to the board


## Roadmap 

Big Picture Description
---
Name ideas: toy, toy synth

toy is a 2 oscillator synthesizer with semi-modular signal routing through filters and FX modules. It is also a 16 step
sequencer with recordable parameter input.

Synth overview
- 2 tone generating oscillators (OSC1 & OSC2)
- Phase offset for OSC2
- 4 voices
- pitch bend
- 2 assignable LFOs
- Onboard FX:
  - Delay
  - Distortion
  - Phase
-2 amp envelopes (1 for each OSC)
-1 assignable envelope
-3 LPF
    
Sequencer Overview:
    

## Ideas
    Wavetable?

Can the voice management logic be listener callbacks?