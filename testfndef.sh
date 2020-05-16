#!/bin/bash
gcc -c outn.c

./ecc "main(){out2(1,2);return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return func2(a,b)*100+func2(c,d);}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "main(){out1(func2(1,2));return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return func2(a,b)*100+func2(c,d);}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "main(){out4(1,2,3,4);return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "main(){out1(func4(1,2,3,4));return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "main(){for(i=1;i<=10;i=i+1){out1(fib(i));} return 0;} fib(n){if(n<=2)return 1;else return fib(n-2)+fib(n-1);} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "main(){for(i=1;i<=3;i=i+1){for(j=1;j<=3;j=j+1){out1(func2(i,j));}} return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "main(){for(i=1;i<=3;i=i+1){j=1;while(j<=3){out1(func2(i,j));j=j+1;}} return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "main(){i=1;while(i<=3){for(j=1;j<=3;j=j+1){out1(func2(i,j));}i=i+1;} return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "main(){i=1;while(i<=3){j=1;while(j<=3){out1(func2(i,j));j=j+1;}i=i+1;} return 0;} func2(a,b){return a*10+b;} func4(a,b,c,d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

echo Done.
