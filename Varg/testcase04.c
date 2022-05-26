// Sean Szumlanski
// COP 3502, Spring 2017

// ==================
// Varg: testcase04.c
// ==================
// A simple test of the mostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = mostFrequentChar(5, 'a', 'a', 'b', 'b', 'a');

	if (c == 'a')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
