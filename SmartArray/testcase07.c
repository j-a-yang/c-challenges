// Patrick Thompson
// COP 3502, Spring 2017

// ========================
// SmartArray: testcase07.c
// ========================
// If this breaks your program check your return values for trimSmartArray and
// your insertElement code


#include <stdio.h>
#include <string.h>
#include "SmartArray.h"

int main(void)
{
	int i; char myString[100], *temp;
	SmartArray *smarty = createSmartArray(10);
	SmartArray *smarty2, *smarty2_trimmed, *smarty4;
	smarty = destroySmartArray(smarty);
	if (trimSmartArray(smarty) != NULL)
		printf("Fail Whale :(\n");

	smarty2 = createSmartArray(-100);
	for (i = 0; i < 10; i++) {
		sprintf(myString, "(string %02d)", i);

		// add string to end of smart array
		temp = insertElement(smarty2, 10, myString);

		// print a little notification that the string was added
		printf("Inserted string: %s\n", temp);
	}

	// Testing your trim return value
	smarty2_trimmed = trimSmartArray(smarty2);
	smarty2 = NULL;

	// add some strings to the smart array
	for (i = 10; i < 14; i++)
	{
		// format my string
		sprintf(myString, "(string %02d)", i);

		// add string to end of smart array
		temp = insertElement(smarty2_trimmed, i - 11, myString);

		// print a little notification that the string was added
		printf("Inserted string: %s\n", temp);
	}

	printSmartArray(smarty2_trimmed);

	// Standard bamboozlement, goes above size on purpose
	for (i = 0; i < 22; i++) {
		removeElement(smarty2_trimmed, i);
	}
	printf("Oh noes you've been bamboozled!\n");

	// print out the contents of the smart array
	printSmartArray(smarty2_trimmed);

	trimSmartArray(smarty2_trimmed);

	smarty = destroySmartArray(smarty2_trimmed);
	return 0;
}
