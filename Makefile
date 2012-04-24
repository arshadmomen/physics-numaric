CC=gcc
CFLAGS=-O3 -c
LDFLAGSMAT=-lblas -llapack
LDFLAGSHIST=-lgsl -lgslcblas -lm

all:mat.o hist.o
	$(CC) mat.o $(LDFLAGSMAT) -o mat.out
	$(CC) hist.o $(LDFLAGSHIST) -o hist.out

mat.o:mat.c
	$(CC) $(CFLAGS) mat.c

hist.o:hist.c
	$(CC) $(CFLAGS) hist.c

clean:
	rm -rf *.o *.out
