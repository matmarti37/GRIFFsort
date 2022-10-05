CC = g++
CFLAGS   = -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/utils\
      -I$(GRIFFsort)/current/calibrator

BIN=$(GRIFFsort)/bin/sfu

SORT= sort.o\
      $(GRIFFsort)/current/SFU-format/SFU-format.a\
      $(GRIFFsort)/current/calibrator/calibrator.a\
      $(GRIFFsort)/current/midas/decoder/decoder.a\
      $(GRIFFsort)/current/utils/utils.a


sort:$(SORT)
	$(CC) -o $(BIN)/sfu_Tigress_BGOTCal $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c sort.h
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
