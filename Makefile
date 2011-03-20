CC = gcc

OBJDIR = obj
TARGETDIR = .
TARGET = facenect
DEFINES = -DIS_SIM=0
INCLUDES = -Ilibfreenect/include -Ilibfreenect/wrappers/c_sync 
CPPFLAGS = $(DEFINES) $(INCLUDES)
CFLAGS = -Wall -O2
CXXFLAGS = $(CFLAGS)
LDFLAGS = -Wall -rdynamic -Wl,-rpath,libfreenect/build/lib:  
LIBS = -lGLU -lGL -lSM -lICE -lX11 -lXext -lglut -lXmu -lXi -lusb-1.0 -lpthread -lm libfreenect/build/lib/libfreenect.so.0.0.1 libfreenect/build/lib/libfreenect_sync.so.0.0.1

all: facenect

facenect: facenect.c.o
	echo "foo"
	$(CC) -o $@ $(LDFLAGS) $(LIBS) $^

%.c.o: %.c
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f *.o facenect

