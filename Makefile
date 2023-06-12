CC=g++
CFLAGS=-Wall -std=c++14
BINS=tarea
all: clean problema1

tarea:
	$(CC) $(CFLAGS) -o problema1 problema1.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)