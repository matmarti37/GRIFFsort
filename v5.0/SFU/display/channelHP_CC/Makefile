CC = g++
CFLAGS   = -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/decoder

BIN=$(GRIFFsort)/bin/sfu

SORT= sort.o\
       $(GRIFFsort)/current/SFU-format/SFU-format.a

sort:$(SORT)
	$(CC) -o $(BIN)/sfu_display_channelHP_CC $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
