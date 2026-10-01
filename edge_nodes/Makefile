CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I include

main.out: main.o parse_csv.o
	$(CC) main.o parse_csv.o -o main.out

main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

parse_csv.o: src/parse_csv.c
	$(CC) $(CFLAGS) -c src/parse_csv.c -o parse_csv.o

clean:
	rm -f *.o main.out

#CC is compiler, CFLAGS -Wall, -Wextra to catch bugs normal wouldnt, -I include to sepcify we're loading in included data
# in line 4, main.out is target with main.o and parse_csv.o being prereqs
# compile individually, with file paths to ensure full accuracy, and ideal time since only recently edited files will be recompiled.
