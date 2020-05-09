#!/bin/bash
./ecc "a=b=c=1;foo3(a+1,2*b,3-c);"> tmp.s
gcc -c foo.c
gcc -o tmp tmp.s foo.o
./tmp

./ecc "foo3((2,1),(1,2),(1,2,3));"> tmp.s
gcc -c foo.c
gcc -o tmp tmp.s foo.o
./tmp

./ecc "foo6(1,2,3,4,5,6);"> tmp.s
gcc -c foo.c
gcc -o tmp tmp.s foo.o
./tmp

./ecc "foo6(1,2,3,4,5,6,7);"> tmp.s
gcc -c foo.c
gcc -o tmp tmp.s foo.o
./tmp

echo OK
