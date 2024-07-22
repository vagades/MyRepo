#!/bin/bash

ASM = nasm
ASMFLAGS = -f elf64 -g

LD = gcc
LDFLAGS = -no-pie -fno-pie

SRC_DIR = source
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.asm)
OBJS = $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(LD) $(LDFLAGS) $^ $(OBJ_DIR)/macro.c -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm | $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) -I$(INC_DIR) $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@


clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
