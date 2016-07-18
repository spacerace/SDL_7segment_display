CC=gcc
LINK=-lSDL_gfx -lSDL

all:
	$(CC) $(LINK) -Wall 7seg.c -o 7seg
	$(CC) $(LINK) -Wall 7seg-editor.c -o 7seg-editor
