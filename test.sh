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

try 0 0
try 1 1
try 41 41
try 42 42
try 123 123
try 21 "5+20-4"
try 41 " 12 + 34 - 5 "
#try 1 "1+-2"
#try 1 " 1 + foo + 5"
try 47 " 5 + 6 * 7 "
try 15 "5*(9-6)"
try 4 "(3+5)/2"
try 99 "(((99)))"
try 3 "-3*(1-2)"

echo OK