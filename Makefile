CC=g++ -O3 -fopenmp -o prog
CFLAGS=-Wall -std=c++14
BINS=problema1 problema2 grafo
all: clean problema1 problema2 grafo

problema1:
	$(CC) $(CFLAGS) -o problema1 problema1.cpp

problema2:
	$(CC) $(CFLAGS) -o problema2 problema2.cpp

grafo:
	$(CC) $(CFLAGS) -o grafo grafo.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)