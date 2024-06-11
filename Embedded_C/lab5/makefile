# make_file
# ENG\ Mohanad

# Compiler
cc = arm-none-eabi-
CFLAGS = -mthumb -gdwarf-2 -g -std=c99
INCS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
Project_name = Mohanad

all: $(Project_name).bin
	@echo "==== Build is Done ===="

%.o: %.c
# $ arm-none-eabi-gcc -E -mthumb -mcpu=cortex-m3 main.c -o main.i
	$(cc)gcc $(CFLAGS) $(INCS) -c $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(cc)ld -T linker_script.ld $(LIBS) $^ -o $@ -Map=Map_file.map 
	cp $@ $(Project_name).axf


$(Project_name).bin: $(Project_name).elf
	$(cc)objcopy -O binary $< $@

clear_all:
	rm -f *.o *.elf *.bin

clear: clear_all
	rm -f *.elf *.bin
