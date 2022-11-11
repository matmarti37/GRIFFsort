CC = g++
CFLAGS   = -g -O3 -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
BIN = $(GRIFFsort)/current/utils
INC = -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(ROOTINC)

UTILS=read_master.o\
      lin_eq_solver.o\
      get_sin_par.o\
      waveform_analyzer.o

utils:$(UTILS) addspn chisqspn calibrationAttempt
	$ ar rcs $(BIN)/utils.a $(UTILS)
	mv addspn $(GRIFFsort)/bin
	mv chisqspn $(GRIFFsort)/bin
	mv calibrationAttempt $(GRIFFsort)/bin

read_master.o:read_master.c read_master.h
	$(CC) -c -o read_master.o $(CFLAGS) read_master.c -I$(INC)

lin_eq_solver.o:lin_eq_solver.c lin_eq_solver.h
	$(CC) -c -o lin_eq_solver.o $(CFLAGS) lin_eq_solver.c -I$(INC)

get_sin_par.o:get_sin_par.c get_sin_par.h
	$(CC) -c -o get_sin_par.o $(CFLAGS) get_sin_par.c -I$(INC)

waveform_analyzer.o:waveform_analyzer.c waveform_analyzer.h
	$(CC) -c -o waveform_analyzer.o $(CFLAGS) waveform_analyzer.c -I$(INC) $(ROOT)

addspn:
	$(CC) -o addspn $(CFLAGS) addspn.c -I$(INC)
chisqspn:
	$(CC) -o chisqspn $(CFLAGS) chisqspn.c -I$(INC)
clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort addspn chisqspn calibrationAttempt
