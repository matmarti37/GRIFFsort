CC = g++
CFLAGS   = -g -O3 -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(ROOTINC)
 
BIN=$(GRIFFsort)/current/midas/state-machine

SORT_NOT_ASSEMBLE= sort_but_not_assemble.o

all:  sort_but_not_assemble

sort_but_not_assemble:$(SORT_NOT_ASSEMBLE)
	$ ar rcs $(BIN)/sort_but_not_assemble.a $(SORT_NOT_ASSEMBLE)

sort_but_not_assemble.o:sort_but_not_assemble.c sort_but_not_assemble.h 
	$(CC) -c -o sort_but_not_assemble.o sort_but_not_assemble.c $(CFLAGS) $(INC)


clean:
	rm -rf *.o *~
very-clean:
	rm -rf *.a *.o *.*~ *~
