# make_file
# ENG\ Mohanad

# Compiler
cc = arm-none-eabi-
CFLAGS = -mthumb -gdwarf-2
INCS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
Project_name = Mohanad-cortex-m3

all: $(Project_name).bin
	@echo "==== Build is Done ===="

%.o: %.c
	$(cc)gcc $(CFLAGS) $(INCS) -c $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(cc)ld.exe -T linker_script.ld $(LIBS) $^ -o $@ -Map=Map_file.map

$(Project_name).bin: $(Project_name).elf
	$(cc)objcopy -O binary $< $@

clear_all:
	rm -f *.o *.elf *.bin

clear: clear_all
	rm -f *.elf *.bin
