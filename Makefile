CC=g++
CFLAGS=-Wall -std=c++14
BINS=problema1 problema2
all: clean problema1 problema2

problema1:
	$(CC) $(CFLAGS) -o problema1 problema1.cpp

problema2:
	$(CC) $(CFLAGS) -o problema2 problema2.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)