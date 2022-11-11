CC = g++
CFLAGS   = -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/midas/state-machine
BIN=$(GRIFFsort)/bin/midas
SORT= sort.o\
       $(GRIFFsort)/current/midas/state-machine/sort_but_not_assemble.a\
       $(GRIFFsort)/current/SFU-format/SFU-format.a\
       $(GRIFFsort)/current/midas/decoder/decoder.a\
       $(GRIFFsort)/current/utils/utils.a
sort:$(SORT)
	$(CC) -o $(BIN)/wfit_show_bad_tmax $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
