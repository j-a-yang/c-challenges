// Sean Szumlanski
// COP 3502, Spring 2017

// ==================
// Varg: testcase02.c
// ==================
// A simple test of the mostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = mostFrequentChar(7, 'a', 'b', 'c', 'd', 'd', 'b', 'a');

	if (c == 'd')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
