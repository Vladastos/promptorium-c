
CC = gcc
CFLAGS = -g -Wall -fanalyzer
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
BIN = promtporium

SRC_DIR = src
SRC = $(SRC_DIR)/main.c


all: run

build:
	if [ -f $(BIN_DIR)/$(BIN) ]; then rm -rf $(BIN_DIR)/$(BIN); fi
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN) $(SRC) $(SRC_DIR)/*/*.c

run: 
	if [ ! -f $(BIN_DIR)/$(BIN) ]; then make build; fi
	$(BIN_DIR)/$(BIN)

lint:
	$(CC) $(CFLAGS) -fsyntax-only  $(SRC)

format:
	clang-format -i $(SRC)

clean:
	rm -rf $(BIN_DIR)/*

deploy: all
	sudo cp $(BIN_DIR)/$(BIN) /usr/local/bin
	sudo chmod +x /usr/local/bin/$(BIN)

uninstall:
	sudo rm /usr/local/bin/$(BIN)

.PHONY: all build run lint format clean deploy uninstall
