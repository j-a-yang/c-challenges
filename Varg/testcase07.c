// John Yang
// COP 3502, Spring 2017

// ==================
// Varg: testcase07.c
// ==================
// A simple test of the fancyMostFrequentChar() function.

#include <stdio.h>
#include "Varg.h"

int main(void)
{
	char c = fancyMostFrequentChar('\0', '\0', 'c', 'r', 'r', 'r', 'a', 'a', '\0');

	if (c == '\0')
		printf("Hooray!\n");
	else
		printf("fail whale :(\n");

	return 0;
}
