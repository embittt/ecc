#include <stdio.h>
int func2(int, int);
int func4(int, int, int, int);

int out1(int i0)
{
	return printf("[%d]\n", i0);
}

int out2(int i0, int i1)
{
	return printf("[%d]\n", func2(i0, i1));
}

int out4(int i0, int i1, int i2, int i3)
{
	return printf("[%d]\n", func4(i0, i1, i2, i3));
}

