# 🔹 Project Name (Output File)
TARGET = main

# 🔹 Microcontroller Model
MCU = atmega328pb

# 🔹 Clock Frequency (Matches F_CPU in your code)
F_CPU = 16000000UL

# 🔹 Compiler & Tools
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# 🔹 Compiler Flags
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -I.

# 🔹 Source Files (Update to include subdirectories as needed)
SRCS = main.c startupcode.c MCAL/GPIO/gpio.c MCAL/USART/Atmega328pb_USART.c

# 🔹 Linker Flags (Disable default startup files and libraries, use custom linker script)
LDFLAGS = -nostartfiles -nodefaultlibs -T LinkerScript.ld -lgcc



# 🔹 Object Files
OBJS = $(SRCS:.c=.o)

# 🔹 Output HEX File
TARGET_HEX = $(TARGET).hex

# 🔹 Programmer (Modify based on your setup)
PROGRAMMER = usbasp

# 🔹 AVRDUDE Port (Needed for Arduino ISP, leave empty for USBasp)
PORT =

# 🔹 Build Rules
all: $(TARGET_HEX)

$(TARGET_HEX): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJS) $(LDFLAGS)
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET_HEX)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(TARGET_HEX)
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -U flash:w:$(TARGET_HEX):i

clean:
	rm -f *.o *.elf *.hex
