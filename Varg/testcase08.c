// John Yang
// COP 3502, Spring 2017

// ==================
// Varg: testcase08.c
// ==================
// A simple test of the mostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = mostFrequentChar(9, 'a', 'a', 'l', 'i', 'o', 'd', 'd', 'd', 'a');

	if (c == 'd')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
