# TODO

- a way to map buttons to midi notes, aka configurable scales
    - what does that take?
    - a control struct
      - with a collection of inputs and outputs
      - nodes take input objects, which can be scaled hardware inputs or scaled software inputs
      - something to represent the signal nodes
    - an I/O buffer (the pinout file?)

## MCP23008
start up:
- start bit
- control word (the mcp address plus R/W bit)
- write 1 << 4 to 0x05 (iocon, sets to byte mode)
- write 0b1111_1111 to gppu (sets internal pullup resistors)
- stop 