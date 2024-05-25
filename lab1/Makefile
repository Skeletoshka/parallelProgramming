all : sse loop

sse : sse.c
	gcc sse.c -o sse

loop : loop.c
	gcc loop.c -o loop

.PHONY : time clean

time :
	./timeit

clean : -rm -f sse loop