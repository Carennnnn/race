OBJ = graphics.o init.o main.o thread.o


all: graphics init main thread
	gcc -o a4 $(OBJ) -lpthread -lncurses

graphics: graphics.c defs.h
	gcc -c graphics.c

init: init.c defs.h
	gcc -c init.c

main: main.c defs.h
	gcc -c main.c

thread: thread.c defs.h
	gcc -c thread.c

clean:
	rm -f $(OBJ) a4
