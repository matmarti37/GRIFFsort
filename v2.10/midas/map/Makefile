CC = g++
CFLAGS   = -O3 -Wall -fPIC

BIN = $(GRIFFsort)/current/midas/map
INC = -I$(GRIFFsort)/current/SFU-format\
      -I$(GRIFFsort)/current/midas/decoder\
      -I$(GRIFFsort)/current/utils\
      -I$(ROOTINC)
MAP=map.o

map:$(MAP)
	$ ar rcs $(BIN)/map.a $(MAP)


map.o:map.c map.h
	$(CC) -c -o map.o $(CFLAGS) map.c $(INC)

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
