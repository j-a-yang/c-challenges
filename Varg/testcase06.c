// Sean Szumlanski
// COP 3502, Spring 2017

// ==================
// Varg: testcase06.c
// ==================
// A simple test of the mostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = mostFrequentChar(0);

	if (c == '\0')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
