cc = arm-none-eabi-
CFLAGS = -g -mcpu=arm926ej-s
INCS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name=Mohanad

all: $(Project_name).bin
	@echo "==== Build is Done ===="

startup.o: startup.s
	$(cc)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(cc)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(cc)ld.exe -T linker_script.ld $(LIBS) $^ -o $@ -Map=Map_file.map

$(Project_name).bin: $(Project_name).elf
	$(cc)objcopy.exe -O binary $< $@

clear_all:
	rm *.o *.elf *.bin

clear: clear_all
	rm *.elf *.bin
