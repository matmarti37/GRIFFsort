CC = g++
CFLAGS   = -O -Wall -fPIC
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(GRIFFsort)/current/list/state-machine\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/midas/map\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/utils\
      -I$(ROOTINC)

BIN=$(GRIFFsort)/bin/list
SORT= sort.o\
       $(GRIFFsort)/current/list/state-machine/read_and_sort_list.a\
       $(GRIFFsort)/current/midas/map/map.a\
       $(GRIFFsort)/current/utils/utils.a\
       $(GRIFFsort)/current/midas/decoder/decoder.a
sort:$(SORT)
	$(CC) -o $(BIN)/list_event_rate $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
