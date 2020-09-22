# This is a Makefile for the mmn22 project
CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CCLINK = $(CC)
LIBS = -lm
OBJS = mycomp.o complex.o
RM = rm -f
# Creating the executable (mmn22)
mmn22: $(OBJS)
	$(CCLINK) -o mmn22 $(OBJS) $(LIBS)

# Creating object files using default rules
mycomp.o: mycomp.c complex.h
complex.o: complex.c complex.h
# Cleaning old files before new make
clean:
	$(RM) mmn22 screen_test *.o *.bak *~ "#"* core
