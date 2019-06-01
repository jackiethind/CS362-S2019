CFLAGS= -Wall -fpic -coverage -lm -std=c99

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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomAdventurer: randomadventurer.c dominion.o rngs.o
	gcc randomadventurer.c dominion.c rngs.c -o randomadventurer $(CFLAGS)

randomtest1: randomtestcard1.c dominion.o rngs.o
	gcc randomtestcard1.c dominion.c rngs.c -o randomtestcard1 $(CFLAGS)

randomtest2: randomtestcard2.c dominion.o rngs.o
	gcc randomtestcard2.c dominion.c rngs.c -o randomtestcard2 $(CFLAGS)

randomtestresults: randomadventurer.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	./randomadventurer > randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

utest1: unittest1.c dominion.o rngs.o
	gcc unittest1.c dominion.c rngs.c -o unittest1 $(CFLAGS)

utest2: unittest2.c dominion.o rngs.o
	gcc unittest2.c dominion.c rngs.c -o unittest2 $(CFLAGS)

utest3: unittest3.c dominion.o rngs.o
	gcc unittest3.c dominion.c rngs.c -o unittest3 $(CFLAGS)

utest4: unittest4.c dominion.o rngs.o
	gcc unittest4.c dominion.c rngs.c -o unittest4 $(CFLAGS)

ctest1: cardtest1.c dominion.o rngs.o
	gcc cardtest1.c dominion.c rngs.c -o cardtest1 $(CFLAGS)

ctest2: cardtest2.c dominion.o rngs.o
	gcc cardtest2.c dominion.c rngs.c -o cardtest2 $(CFLAGS)

ctest3: cardtest3.c dominion.o rngs.o
	gcc cardtest3.c dominion.c rngs.c -o cardtest3 $(CFLAGS)

ctest4: cardtest4.c dominion.o rngs.o
	gcc cardtest4.c dominion.c rngs.c -o cardtest4 $(CFLAGS)

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
