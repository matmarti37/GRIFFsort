CC = g++
CFLAGS   = -g -O3 -Wall -fPIC 

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(GRIFFsort)/current/midas/decoder\
      -I$(ROOTINC)
 
BIN=$(GRIFFsort)/current/midas/state-machine

SORT_NOT_ASSEMBLE= sort_but_not_assemble.o
SORT_AND_ASSEMBLE_LIST= sort_and_assemble_list.o

all:  sort_but_not_assemble sort_and_assemble_list

sort_but_not_assemble:$(SORT_NOT_ASSEMBLE)
	$ ar rcs $(BIN)/sort_but_not_assemble.a $(SORT_NOT_ASSEMBLE)

sort_but_not_assemble.o:sort_but_not_assemble.c sort_but_not_assemble.h 
	$(CC) -c -o sort_but_not_assemble.o sort_but_not_assemble.c $(CFLAGS) $(INC)

sort_and_assemble_list:$(SORT_AND_ASSEMBLE_LIST)
	$ ar rcs $(BIN)/sort_and_assemble_list.a $(SORT_AND_ASSEMBLE_LIST)

sort_and_assemble_list.o:sort_and_assemble_list.c sort_and_assemble_list.h 
	$(CC) -c -o sort_and_assemble_list.o sort_and_assemble_list.c $(CFLAGS) $(INC)

clean:
	rm -rf *.o *~
very-clean:
	rm -rf *.a *.o *.*~ *~
