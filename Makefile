
all: subs-kmp

subs-kmp: substring.o strsearch-kmp.o strings.o
	gcc -Wall -std=c99 substring.o strsearch-kmp.o strings.o -o subs-kmp

substring.o: substring.c strsearch.h strings.h
	gcc -Wall -std=c99 -g substring.c -c

strsearch-kmp.o: strsearch-kmp.c strsearch.h strings.h
	gcc -Wall -std=c99 -g strsearch-kmp.c -c

strings.o: strings.c strings.h
	gcc -Wall -std=c99 -g strings.c -c

clean:
	rm -f *.o subs-kmp
