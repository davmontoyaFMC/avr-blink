# AVR Bare-Metal Blink

Installed a toolchain from scratch and wrote C directly against hardware registers to blink an LED on the UNO R3 board without the Arduino IDE.

## Overview

This project blinks an LED on the board, but the instructions are written at the register level rather than through the Arduino IDE. I built it this way to actually understand the datasheet and how the chip's pins are controlled, and to set up a build I run myself with a Makefile. The goal is to strengthen my firmware skills by working close to the hardware.

## Hardware

- Elegoo UNO (ATmega328P, 8-bit AVR, 16 MHz) — an Arduino UNO-compatible board
- On-board LED wired to pin 13 (chip pin PB5) — no external wiring needed

## Toolchain

- **avr-gcc** — C compiler targeting AVR
- **avrdude** — flashing tool (uploads to the board over USB)
- **GNU make** — build automation
- Installed on Windows via the Scoop package manager

## Build & Flash

```
make          # compile and convert to Intel HEX
make flash    # build (if needed) and flash to the board
make clean    # delete generated .elf / .hex files
```

Set the correct COM port in the `Makefile` (`PORT = COM3`) before flashing.

## How It Works

First the code configures the LED's pin as an output by setting bit 5 of the data-direction register `DDRB`. Then an infinite loop turns the LED on, waits 500 ms, turns it off, and waits another 500 ms. The delays are what make the state change visible — without them the LED would switch far too fast to see.

The pin is controlled with the bitmask `1 << 5`, which is the value `00100000` — a mask that isolates bit 5 (the LED's pin) while ignoring the other seven. The mask only selects *which* bit; the *operator* decides the action. `PORTB |= (1 << 5)` uses OR to set bit 5 high (LED on). `PORTB &= ~(1 << 5)` clears it (LED off): `~` flips every bit of the mask to `11011111`, so the AND forces bit 5 to 0 while leaving the other bits untouched.

This read-modify-write approach means I change a single pin without disturbing the rest of the port — which matters on a real chip where other bits in the same register control other pins.

## Roadmap

Starting point: understand the tools and datasheet, write register-level C, and automate the build.

- Replace the blocking `_delay_ms()` with a hardware timer interrupt
- Interrupt-driven UART, SPI, and I2C drivers written from the datasheet
- A cooperative task scheduler
- A UART command shell

## Notes

Learned to watch Notepad's habit of silently appending a `.txt` extension when saving files like `Makefile` or `.gitignore` that aren't supposed to have one.