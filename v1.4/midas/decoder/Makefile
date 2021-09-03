CC = g++
CFLAGS   = -O3 -Wall -fPIC

BIN = $(GRIFFsort)/current/midas/decoder

DECODER=midas-format.o grif-format.o

decoder:$(DECODER)
	$ ar rcs $(BIN)/decoder.a $(DECODER)

grif-format.o:grif-format.c grif-format.h
	$(CC) -c -o grif-format.o $(CFLAGS) grif-format.c

midas-format.o:midas-format.c midas-format.h
	$(CC) -c -o midas-format.o $(CFLAGS) midas-format.c

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
