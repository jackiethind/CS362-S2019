cmake_minimum_required(VERSION 3.10)
project(dominion C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dominion
        badTestDrawCard.c
        betterTestDrawCard.c
        dominion.c
        dominion.h
        dominion_helpers.h
        interface.c
        interface.h
        playdom.c
        player.c
        rngs.c
        rngs.h
        rt.c
        supplyTest.c
        testBuyCard.c
        testDrawCard.c
        testInit.c
        testShuffle.c
        unittest1.c
        unittest2.c
        unittest3.c
        unittest4.c cardTest1.c cardTest2.c cardTest3.c cardTest4.c randomtestadventurer.c randomtestcard1.c randomtestcard2.c)
