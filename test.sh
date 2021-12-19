#!/bin/sh


gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g *.c -o pa3 && ./pa3 ./examples/4_5.b ./outputs/4_5.t ./outputs/4_5.f ./outputs/4_5.p