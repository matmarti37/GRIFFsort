CC = g++
CFLAGS   = -O3 -Wall -fPIC

BIN = $(GRIFFsort)/current/midas/decoder

DECODER=midas-format.o grif-format.o

decoder:$(DECODER)
	$ ar rcs $(BIN)/decoder.a $(DECODER)

grif-format.o:grif-format.c grif-format.h
	$(CC) -c -o grif-format.o $(CFLAGS) grif-format.c

midas-format.o:midas-format.c
	$(CC) -c -o midas-format.o $(CFLAGS) midas-format.c

grif-replay:grif-replay.c midas-format.c grif-format.c util.c
	 gcc -g -o grif-replay grif-replay.c midas-format.c grif-format.c util.c -lm
clean:
	rm -rf *.o grif-replay

very-clean:
	rm -rf *.a *.o *.*~ *~ sort grif-replay
