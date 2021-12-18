#!/bin/sh

git add --all && git commit -m "." && gcc -std=c99 -pedantic -Wvla -Wall -Wshadow -g *.c -o pa3 && ./pa3 ./examples/4_5.b