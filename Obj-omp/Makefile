#Dirs
ROOT=..
EXEDIR=$(ROOT)/
SRCDIR=$(ROOT)/src/
HEADDIR=$(ROOT)/include/
LIBDIR=$(ROOT)/Obj-omp/
OBJDIR=../Obj-omp/

# -*- Makefile -*-
SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -g -fopenmp -std=c99 -O3 -ffast-math -fomit-frame-pointer -I$(HEADDIR)
LDLIBS=-lm -L$(LIBDIR) -Wl,-rpath,Obj-omp -Wl,-rpath,../Obj-omp

MAIN=$(ROOT)/main

SRC=$(wildcard ../src/*.c)
OBJ=$(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

TARGET=$(EXEDIR)ljmd-omp.x

.PHONY: clean

default: $(TARGET)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c -fPIC $(CFLAGS) $<

clean:
	rm -f *.mod *.o $(EXEDIR)ljmd-omp.x $(EXEDIR)*.o $(LIBDIR)libljomp.so $(SRCDIR)*.o

$(LIBDIR)libljomp.so: $(OBJ) $(HEADDIR)ljmd.h 
	$(CC) -shared $(OBJ) -o $(LIBDIR)libljomp.so

$(TARGET): $(MAIN).c $(LIBDIR)libljomp.so $(HEADDIR)ljmd.h 
	$(CC) $(LDLIBS) $(CFLAGS) -o $(EXEDIR)ljmd-omp.x $(MAIN).c -lljomp
