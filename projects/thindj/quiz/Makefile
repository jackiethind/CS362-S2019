CFLAGS = -Wall -fpic -coverage -lm -std=c99 -ftest-coverage

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

test:
	echo "Running test for random quiz"
	make testme
	- ./testme
	gcov -fb testme.c

clean:
	rm -f *.o *.gcda *gcno testme.exe