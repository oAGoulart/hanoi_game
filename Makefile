# Augusto Goulart (1901560080) 28/03/2023 12:54:00
CC = gcc
CFLAGS = -g -Wformat=0
MD = mkdir
RM = rm

OUT_DIR = bin/
SRC_DIR = src/

PROJECT = hanoi_game
SOURCES = terminal.c list.c stack.c game.c disc.c vector.c main.c 
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
