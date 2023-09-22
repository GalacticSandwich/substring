
CC := gcc
CFLAGS := -std=c99 -Wall -O2
OFLAGS := -g -DEOP

all: subs-kmp clean

subs-kmp: substring.o strsearch-kmp.o strings.o
	$(CC) $(CFLAGS) substring.o strsearch-kmp.o strings.o -o subs-kmp

substring.o: substring.c strsearch.h strings.h
	$(CC) $(CFLAGS) $(OFLAGS) substring.c -c

strsearch-kmp.o: strsearch-kmp.c strsearch.h strings.h
	$(CC) $(CFLAGS) $(OFLAGS) strsearch-kmp.c -c

strings.o: strings.c strings.h
	$(CC) $(CFLAGS) $(OFLAGS) strings.c -c

clean:
	rm -f *.o
