INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
#LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
LIBRARIES = -lX11 -lglut -lGL -lGLU -lm

All: ufo

ufo: ufo.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)

clean:
	rm -rf ufo *.o
