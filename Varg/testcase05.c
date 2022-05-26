// Sean Szumlanski
// COP 3502, Spring 2017

// ==================
// Varg: testcase05.c
// ==================
// A simple test of the fancyMostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = fancyMostFrequentChar('a', 'a', 'b', 'b', 'a', '\0');

	if (c == 'a')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
