CC=g++
CFLAGS=-Wall -std=c++14
BINS=problemaB1 problemaB2
all: clean problemaB1 problemaB2

problema1:
	$(CC) $(CFLAGS) -o problemaB1 problemaB1.cpp

problema2:
	$(CC) $(CFLAGS) -o problemaB2 problemaB2.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)