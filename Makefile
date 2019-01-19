CC=g++
CFLAGS=-W -Wall -ansi -pedantic -std=c++11
LDFLAGS=
EXEC=bowling_score

all: $(EXEC)

bowling_score: bowling.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

bowling.o: src/bowling.cpp include/bowling.h
	$(CC) -o $@ -c $< $(CFLAGS)

main.o: src/main.cpp include/bowling.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o bowling_score
