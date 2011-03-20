CFLAGS = -g
LDFLAGS = -g
LDLIBS = -lGL -lGLU -lglut

all: mesh meshview

mesh: mesh.o linkedlist.o shape.o

mesh.o: mesh.c linkedlist.h shape.h

linkedlist.o: linkedlist.c linkedlist.h

shape.o: shape.c shape.h

meshview: meshview.o

meshview.o: meshview.c

clean:
	rm -f mesh meshview *.o

