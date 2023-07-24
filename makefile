CC=g++ -std=c++11
CFLAGS=-g -Wall -O3 -fast
IFLAGS=-I/opt/X11/include
LFLAGS=-L/opt/X11/lib -lX11
all: shift2

shift2: shift2.cc graphics.cc julia.cc mandelbrot.cc lamination.cc green.cc sausage.cc interface.cc
	$(CC) $(CFLAGS) $(IFLAGS) -o shift2 shift2.cc $(LFLAGS) -lm

clean: rm shift2
