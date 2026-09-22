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
