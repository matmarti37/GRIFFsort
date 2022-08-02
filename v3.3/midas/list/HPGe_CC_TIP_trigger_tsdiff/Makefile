CC = g++
CFLAGS   = -O -Wall -fPIC $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(GRIFFsort)/current/midas/state-machine\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/midas/map\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/utils\
      -I$(ROOTINC)

BIN=$(GRIFFsort)/bin/midas

SORT= sort.o\
       $(GRIFFsort)/current/midas/state-machine/sort_and_assemble_list.a\
       $(GRIFFsort)/current/midas/decoder/decoder.a\
       $(GRIFFsort)/current/utils/utils.a\
       $(GRIFFsort)/current/midas/map/map.a

sort:$(SORT)
	$(CC) -o $(BIN)/list_HPGe_CC_TIP_trigger_tsdiff $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
