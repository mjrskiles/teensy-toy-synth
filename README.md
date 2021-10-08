# toy synth

![IMG_1750](https://user-images.githubusercontent.com/17223287/136628141-6d5fe5d3-4705-466a-9222-c0e7e7da51ba.JPEG)

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

## Hardware

![IMG_1565](https://user-images.githubusercontent.com/17223287/136628525-00d37722-524a-4e84-80d3-80b344049b7d.JPEG)

![IMG_1660](https://user-images.githubusercontent.com/17223287/136628574-7a35da4a-c04f-4f15-b230-306e4ad26346.JPEG)

![IMG_1790](https://user-images.githubusercontent.com/17223287/136628652-0ed00920-a731-41c8-9183-796adabf0d62.JPEG)


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
    
    

## Ideas
    Wavetable?

Can the voice management logic be listener callbacks?
