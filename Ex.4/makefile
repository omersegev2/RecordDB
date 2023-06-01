CC = gcc
FLAGS = -std=c99 -Wall -pedantic-errors

LDFLAGS = /Users/omer/Desktop/Ex.4/libprog2.a

SRCS =  main.c records_db.c tracks_db.c

OBJS = $(SRCS:.c=.o)

run: main
	./main

main: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o main

records_db: records_db.c
	$(CC) $(FLAGS) -c records_db.c -o records_db.o

tracks_db : tracks_db.c 
	$(CC) $(FLAGS) -c tracks_db.c -o tracks_db.o

clean:
	rm -f $(OBJS) main