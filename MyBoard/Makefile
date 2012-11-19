TOOLCHAIN=arm-none-linux-gnueabi-
ARM_CPU=arm7tdmi
VPATH = src include
INCLUDE=include
CCFLAGS =  \
	-mcpu=$(ARM_CPU) \
	-mthumb-interwork \
	-ffunction-sections \
	-Os\
	-Wall



all: main.o startup.o lowlevel.o irq.o
	@echo ---------------compiling ------------
	$(TOOLCHAIN)ld  -o board.elf -T ./linker/ROM.ld $?
	@echo ==========================Generating binary file==========================================
	$(TOOLCHAIN)objcopy -O ihex board.elf board.hex
main.o : main.c
	@echo =========================compiling main.c============================================
	$(TOOLCHAIN)gcc $(CCFLAGS) -I$(INCLUDE)   -nostdlib -c $<
lowlevel.o : lowlevel.c lowlevel.h
	@echo =========================compiling lowlevel.c============================================
	$(TOOLCHAIN)gcc $(CCFLAGS) -I$(INCLUDE)   -nostdlib -c $<
startup.o:startup.S
	@echo ===================assembler============================================
	$(TOOLCHAIN)as  -o $@ $<
irq.o : irq.c irq.h
	@echo =========================compiling irq.c============================================
	$(TOOLCHAIN)gcc $(CCFLAGS) -I$(INCLUDE)   -nostdlib -c $<
clean:
	@echo ==========================================cleaning==============================================
	rm -rf *.o  *.elf *.hex *.o





