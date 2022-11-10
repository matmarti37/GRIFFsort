CC = g++
CFLAGS   = -g0 -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)

INC = -I$(ROOTINC)\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/midas/map\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/state-machine

BIN=$(GRIFFsort)/bin/midas
SORT= sort.o\
	$(GRIFFsort)/current/midas/state-machine/sort_but_not_assemble.a\
        $(GRIFFsort)/current/utils/utils.a\
       $(GRIFFsort)/current/midas/map/map.a\
	$(GRIFFsort)/current/midas/decoder/decoder.a
sort:$(SORT)
	$(CC) -o $(BIN)/midas_view_hist_tsup $(SORT) $(CFLAGS) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
