CFLAGS= -Wall -fpic -coverage -lm -std=c99 -ftest-coverage

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unitTest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unitTest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unitTest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unitTest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardTest1: cardTest1.c dominion.o rngs.o
	gcc -o cardTest1 -g cardTest1.c dominion.o rngs.o $(CFLAGS)

cardTest2: cardTest2.c dominion.o rngs.o
	gcc -o cardTest2 -g cardTest2.c dominion.o rngs.o $(CFLAGS)

cardTest3: cardTest3.c dominion.o rngs.o
	gcc -o cardTest3 -g cardTest3.c dominion.o rngs.o $(CFLAGS)

cardTest4: cardTest4.c dominion.o rngs.o
	gcc -o cardTest4 -g cardTest4.c dominion.o rngs.o $(CFLAGS)

unittestresults:
	echo "Result for running dominion unit tests:" > unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	make unitTest1
	./unittest1 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	make unitTest2
	./unittest2 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	make unitTest3
	./unittest3 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	make unitTest4
	./unittest4 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "cardTest1.c:" >> unittestresults.out
	make cardTest1
	./cardTest1 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "cardTest2.c:" >> unittestresults.out
	make cardTest2
	./cardTest2 >> unittestresults.out
	gcov -fb dominion.c >> unittestresults.out

	echo "cardTest3.c:" >> unittestresults.out
	make cardTest3
	./cardTest3 >> unittestresults.out
	gcov -fb dominion.c  >> unittestresults.out

	echo "cardTest4.c:" >> unittestresults.out
	make cardTest4
	./cardTest4 >> unittestresults.out
	gcov -fb dominion.c  >> unittestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

randomtestresults:
	echo "randomtestcard1.c:" >> randomtestresults.out
	make randomtestcard1
	./randomtestcard1 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out

	echo "randomtestcard2.c:" >> randomtestresults.out
	make randomtestcard2
	./randomtestcard2 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out

	echo "randomtestadventurer.c:" >> randomtestresults.out
	make randomtestadventurer
	./randomtestadventurer >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out


interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
