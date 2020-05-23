#!/bin/bash
gcc -c outn.c

./ecc "int main(){out2(1,2);return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return func2(a,b)*100+func2(c,d);}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){out1(func2(1,2));return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return func2(a,b)*100+func2(c,d);}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){out4(1,2,3,4);return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){out1(func4(1,2,3,4));return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){int i;for(i=1;i<=10;i=i+1){out1(fib(i));} return 0;} int fib(int n){if(n<=2)return 1;else return fib(n-2)+fib(n-1);} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){int i;int j;for(i=1;i<=3;i=i+1){for(j=1;j<=3;j=j+1){out1(func2(i,j));}} return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int i;int j;for(i=1;i<=3;i=i+1){j=1;while(j<=3){out1(func2(i,j));j=j+1;}} return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int i;int j;i=1;while(i<=3){for(j=1;j<=3;j=j+1){out1(func2(i,j));}i=i+1;} return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int i;int j;i=1;while(i<=3){j=1;while(j<=3){out1(func2(i,j));j=j+1;}i=i+1;} return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){int a;int c;c=0;a=1;if(a)c=1;else c=2;out1(c); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int a;int c;c=0;a=0;if(a)c=1;else c=2;out1(c); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int a;int b;int c;c=0;a=0;b=0;if(a)if(b)c=1;else c=2;out1(c); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int a;int b;int c;c=0;a=0;b=0;if(a){if(b)c=1;}else c=2;out1(c); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){int x;int y;x=3;y=&x;out1(*y); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

./ecc "int main(){int x;int y;int z;x=3;y=5;z=&y+8;out1(*z); return 0;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp



./ecc "int main(){int x;x=2;out1(add(x)); return 0;} int add(int a){int b;b=10; return a+b;} int func2(int a, int b){return a*10+b;} int func4(int a, int b, int c, int d){return (func2(a,b)*100+func2(c,d));}"> tmp.s
gcc -o tmp tmp.s outn.o
./tmp

echo Done.
