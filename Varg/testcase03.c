// Sean Szumlanski
// COP 3502, Spring 2017

// ==================
// Varg: testcase03.c
// ==================
// A simple test of the fancyMostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = fancyMostFrequentChar('a', 'b', 'c', 'd', 'd', 'b', 'a', '\0');

	if (c == 'd')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
