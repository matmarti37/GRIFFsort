CC = g++
CFLAGS   = -g -O3 -Wall -fPIC 

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/midas/map\
      -I$(ROOTINC)
 
BIN=$(GRIFFsort)/current/list/state-machine

READ_AND_SORT_LIST= read_and_sort_list.o

all:  read_and_sort_list

read_and_sort_list:$(READ_AND_SORT_LIST)
	$ ar rcs $(BIN)/read_and_sort_list.a $(READ_AND_SORT_LIST)

read_and_sort_list.o:read_and_sort_list.c read_and_sort_list.h 
	$(CC) -c -o read_and_sort_list.o read_and_sort_list.c $(CFLAGS) $(INC)

clean:
	rm -rf *.o *~
very-clean:
	rm -rf *.a *.o *.*~ *~
