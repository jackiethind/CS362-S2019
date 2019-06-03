cmake_minimum_required(VERSION 3.10)
project(mattingnDominion C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(mattingnDominion
        badTestDrawCard.c
        betterTestDrawCard.c
        cardtest1.c
        cardtest2.c
        cardtest3.c
        cardtest4.c
        dominion.c
        dominion.h
        dominion_helpers.h
        interface.c
        interface.h
        playdom.c
        player.c
        randomtestcard1.c
        randomtestcard2.c
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
        unittest4.c)
