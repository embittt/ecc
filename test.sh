#!/bin/bash
try() {
  expected="$1"
  input="$2"

  ./ecc "$input" > tmp.s
  gcc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

#try 0 0
#try 1 1
#try 41 41
#try 42 42
try 123 "123;"
try 1 "foo=1;"
try 3 "foo=1;bar = 2;foo + bar;"
try 6 "i1=1;i2=2;i3=3;i1+i2+i3;"
try 6 "_iI1=1;i2=2;i3=3;_iI1+i2+i3;"
#try 6 "1i=1;"
try 3 "return 3;"
try 3 "return 3;return 5;"
try 1 "a=1;"
try 2 "a=b=2;"
try 7 "a=1+2*3;"
try 9 "a=(1+2)*3;"
try 10 "a=9;a+1;"
#try 0 "a+1=5;"
#try 0 "a+b;"
try 21 "5+20-4;"
try 41 " 12 + 34 - 5 ;"
#try 1 "1+-2"
#try 1 " 1 + foo + 5"
try 47 " 5 + 6 * 7 ;"
try 15 "5*(9-6);"
try 4 "(3+5)/2;"
try 99 "(((99)));"
try 3 "-3*(1-2);"
try 1 "2 == 2;"
try 0 "2 == 3;"
try 0 "2 != 2;"
try 1 "2 != 3;"
try 1 " 1 <2;"
try 0 " 2 <2;"
try 0 " 3 <2;"
try 1 " 1 <=2;"
try 1 " 2 <=2;"
try 0 " 3 <=2;"
try 0 " 1> 2;"
try 0 " 2> 2;"
try 1 " 3> 2;"
try 0 " 1 >=2;"
try 1 " 2 >=2;"
try 1 " 3 >=2;"

echo OK
