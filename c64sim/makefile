# makefile for cpu-emu2
# 2015/BHO1
# 18.8.1015: adding rules 
# sudo apt-get install build-essential make libsdl-image1.2-dev
# sudo apt-get install cdecl

#name of alu main test program

CC        := gcc
LLVMCC	  := clang
LD        := ld

#alu
ALU_MODULES   := cpu printers alu memory
ALU_SRC_DIR   := $(addprefix src/,$(ALU_MODULES))
ALU_BUILD_DIR := $(addprefix build/,$(ALU_MODULES))

ALU_SRC       := $(foreach sdir,$(ALU_SRC_DIR), $(filter-out $(sdir)/alu-main.c, $(filter-out $(sdir)/alu.student.c, $(wildcard $(sdir)/*.c))))

ALU_OBJ       := $(patsubst src/%.c,build/%.o,$(ALU_SRC))
ALU_INCLUDES  := $(addprefix -I,$(ALU_SRC_DIR))
INCLUDES  := $(ALU_INCLUDES)






MODULES = cpu printers alu memory graphic
BDIR    = build
SRC_DIR   := $(addprefix src/,$(MODULES))
DEPS := $(addprefix -I,$(SRC_DIR))

_OBJ = graphic-main.o graphic.o cpu.o cpu-util.o decode.o mu-code.o opcode_tbl.o register.o print-cpu.o memory.o flags.o alu.o disassemble.o parser.o
_SRC = graphic/graphic-main.c graphic/graphic.c cpu/cpu.c cpu/cpu-util.c cpu/decode.c cpu/mu-code.c cpu/opcode_tbl.c cpu/register.c cpu/disassemble.c cpu/parser.c printers/print-cpu.c memory/memory.c alu/flags.c alu/alu.c 

#$(patsubst src/%.c,build/%.o,$(_OBJ))
OBJ = $(patsubst %,$(BDIR)/%,$(_OBJ))

vpath %.c $(ALU_SRC_DIR)
VPATH = src/cpu src/printers src/alu src/memory src/graphic
LIBS := -lreadline 
#$(BDIR)/%.o: scr/cpu/%.c src/memory/%.c src/printers/%.c src/alu/%.c src/graphic/%.c $(DEPS)
$(BDIR)/%.o: %.c
	@echo adasdasd
	@echo $(CC) -W -Wall -g  $(ALU_INCLUDES) `sdl2-config --cflags --libs` -c $^ 
	$(CC) -bbb -W -Wall -g  $(ALU_INCLUDES) `sdl2-config --cflags --libs` -c $^ 
#build/graphic-main.o: graphic-main.c
#$(CC) -W -Wall -g -o $@ $^ 

%.o: %.c
	@echo o2c
	@echo $(CC) -W -Wall -g  $(ALU_INCLUDES) `sdl2-config --cflags --libs` -c $^ 
	$(CC) -W -Wall -Wunused-variable -Wunused-parameter -g  $(ALU_INCLUDES) `sdl2-config --cflags --libs` -c $^ 


graphic: $(_OBJ) 
	@echo linking 
	@echo text $(CC) -W -Wall -g  $(ALU_INCLUDES) `sdl2-config --cflags --libs` -c $^ 
	g++ -o $@ $^ src/sid/sidwrapper.o src/sid/SID.o src/sid/Utils.o src/memorygrid/MemoryGrid.o src/memorygrid/memorygridwrapper.o $(CFLAGS) $(LIBS) `sdl2-config --cflags --libs` -lSDL2 -lSDL2_ttf -lm



.PHONY: all checkdirs clean 

#checkdirs: $(BUILD_DIR)

checkdirs:  $(ALU_BUILD_DIR)


clean:
	@echo "\n ram -rf $(ALU_BUILD_DIR) $(BUILD_DIR) running alu-test minimal" $@	$^ 
	@rm -rf $(ALU_BUILD_DIR)
	@rm -rf $(BUILD_DIR)
