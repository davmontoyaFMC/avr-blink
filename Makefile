# ===== Configuration — change these if your setup changes =====
TARGET     = blink
MCU        = atmega328p
PART       = m328p
PROGRAMMER = arduino
PORT       = COM3
BAUD       = 115200

# ===== Tools =====
CC      = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# ===== Compiler flags =====
CFLAGS = -mmcu=$(MCU) -Os

# ===== Rules =====
all: $(TARGET).hex

$(TARGET).elf: $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).elf $(TARGET).c

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(PART) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

clean:
	-del $(TARGET).elf $(TARGET).hex

.PHONY: all flash clean