# Synth

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