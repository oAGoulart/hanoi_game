# 11:34:00 17/05/2022, Augusto Goulart 1901560080

CC = g++
CFLAGS = -g -std=c++2a
MD = mkdir
RM = rm

OUT_DIR = bin/
SRC_DIR = src/

PROJECT = hanoi_game
SOURCES = main.cpp terminal.cpp
SOURCES_ABS = $(addprefix $(SRC_DIR),$(SOURCES))
DEBUG_FLAGS = $(CFLAGS)
RELEASE_FLAGS = $(CFLAGS) -DNDEBUG -O3

.PHONY: all clean debug release

all: debug release

clean:
	$(RM) -f -d -r $(OUT_DIR)

release: debug
	$(MD) -p $(OUT_DIR)release/
	$(CC) $(RELEASE_FLAGS) $(SOURCES_ABS) -o $(OUT_DIR)release/$(PROJECT)

debug:
	$(MD) -p $(OUT_DIR)
	$(CC) $(DEBUG_FLAGS) $(SOURCES_ABS) -o $(OUT_DIR)$(PROJECT)
