
CC = gcc
CFLAGS = -g -Wall -fanalyzer
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
BIN = promptorium

SRC_DIR = src
MODULES_DIR= $(SRC_DIR)/modules
SRC = $(SRC_DIR)/main.c

DEPLODY_DIR = /usr/local/bin

all: run

run: 
	if [ ! -f $(BIN_DIR)/$(BIN) ]; then make build; fi
	$(BIN_DIR)/$(BIN)

build:
	if [ -f $(BIN_DIR)/$(BIN) ]; then rm -rf $(BIN_DIR)/$(BIN); fi
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN) $(SRC) $(MODULES_DIR)/*/*/*.c

lint:
	$(CC) $(CFLAGS) -fsyntax-only  $(SRC)

format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h  $(MODULES_DIR)/*/*.h $(MODULES_DIR)/*/*/*.c $(MODULES_DIR)/*/*/*.h

clean:
	rm -rf $(BIN_DIR)/*

deploy: build
	sudo mkdir -p $(DEPLODY_DIR)
	sudo cp $(BIN_DIR)/$(BIN) $(DEPLODY_DIR)
	sudo chmod +x $(DEPLODY_DIR)/$(BIN)

uninstall:
	sudo rm -rf $(DEPLODY_DIR)/$(BIN)

.PHONY: all build run lint format clean deploy uninstall
