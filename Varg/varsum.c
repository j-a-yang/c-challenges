// Sean Szumlanski
// COP 3502, Spring 2017

// ==============
// Varg: varsum.c
// ==============
// A program to illustrate the creation of variadic functions (functions that
// can take a variable number of parameters).
//
// SEE ALSO:
// http://www.lysator.liu.se/c/c-faq/c-7.html#7-1


#include <stdio.h>
#include <stdarg.h>


// mySum() takes any number of integers as its arguments, with the following
// restriction: the first argument MUST be the number of integers to follow.
// For example, to sum 1, 2, and 3, the proper function call would be:
//
//       mySum(3, 1, 2, 3);
//
// Notice that since there are three integers to be summed, the first argument
// to the function is 3.

int mySum(int first, ...);


// myOtherSum() takes any number of integers as its arguments, but has a
// different restriction: the last integer to be summed will be zero, and zero
// cannot occur anywhere else in the list of arguments. That is to say, the
// function will know to stop summing as soon as it encounters a zero.
//
// For example, the following two functional calls will have the same result:
//
//       myOtherSum(1, 2, 3, 0);
//       myOtherSum(1, 2, 3, 0, 6, 2, 7, 4, 8, 0);

int myOtherSum(int first, ...);


int main(void)
{
	int d;

	// Recall that mySum() requires us to tell it how many integers it is
	// summing up. So in the function call below, the first 5 says, "You're
	// about to see five integers. Sum them up!"

	d = mySum(5, 1, 2, 3, 4, 5);
	printf("Result of mySum(): %d\n", d);

	// myOtherSum, on the other hand, will keep reading integers until it
	// encounters zero. That is why we terminate the following list of arguments
	// with a zero. Otherwise, the function would keep on summing, accessing
	// unpredictable parts of memory in a dangerous attempt to read more
	// integers!

	d = myOtherSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0);
	printf("Result of myOtherSum(): %d\n", d);

	return 0;
}


// First and foremost: when dealing with an arbitrary number of arguments to a
// function, we always capture the first argument explicitly into a variable,
// and then shuttle the rest off to a list, using elipses. Here, we know that
// the first argument to mySum() will always be an integer, so we capture it in
// a variable of type int called "first."

int mySum(int first, ...)
{
	// We're going to hold the sum in a variable called "total," which we
	// initialize to zero. We're also going to use p and i to hold integers
	// later in the function.
	int total = 0;
	int p, i;

	// Now this is where things get crazy. We're declaring a variable of type
	// va_list, called "argp." Basically, argp, is going to hold our list of
	// arguments to this function! To be clear: va_list is a data type, just
	// like int, char, float, and so on.
	va_list argp;

	// This is how we initialize argp. The line basically means, "Okay, argp is
	// a list of arguments to this function. But where does it start? Well, it
	// starts with the first variable passed to this function, which we
	// conveniently named "first." If we had captured that variable under a
	// different name, we would use that name below.
	va_start(argp, first);

	// Now we're ready to get our arguments, one by one, using a loop. Remember
	// that the variable "first" tells us how many there are, so we want to loop
	// "first" number of times.

	for (i = 0; i < first; i++)
	{
		// The line below tells us to get the value of the next argument from
		// the list. (This will start by pulling the variable after "first,"
		// because "first" itself isn't included in the "..." portion of the
		// list.)
		//
		// We have to tell the va_arg() function where to look for these
		// arguments, as well as what type of data we are pulling. We've got all
		// the information we need about our arguments stored in the variable
		// called "argp," so that's our first argument to the va_arg() function.
		// We also know that we're only dealing with integers, so the second
		// argument to va_arg() is int -- the type of data we're reading. If we
		// were reading a different type of data, we would replace "int" with
		// that data type (e.g., "double"). There are some exceptions here,
		// though, which your compiler might warn you about if you encounter
		// them. ;)
		//
		// The resulting value is stored in p.
		//
		// After we pull an integer out of argp, it is removed from the list,
		// and the next time we call the va_arg function, it will give us the
		// next integer in the list.

		p = va_arg(argp, int);

		// And of course, we want to add p to total in order to keep track of
		// the sum as we go. Recall that "total" was intialized to zero at the
		// beginning of the program.

		total += p;
	}

	// This frees up any lingering memory associated with the argp variable and
	// helps ensure that we don't have any memory leaks emanating from this
	// function.
	va_end(argp);

	// Finally, the loop has terminated and we now return the value of "total,"
	// which should be the sum of all the arguments passed to mySum() (except
	// for the first argument, which was just an argument count).

	return total;
}


int myOtherSum(int first, ...)
{
	// These first lines are the same as above, except that we initialize
	// "total" to the value of "first," since in this function, the first
	// argument is actually part of the sequence of integers that we want to
	// sum. We also don't need the variable "i" that was used in the mySum()
	// function, because we don't use a for-loop in this one.
	int total = first;
	int p;
	va_list argp;

	// If the first argument was zero, then we don't even look for more
	// arguments, because the function is supposed to stop summing as soon as we
	// see a zero.
	if (total == 0)
		return 0;

	// Our list setup is the same as before.
	va_start(argp, first);

	// Here we just keep pulling integers off of the argp list until we see a
	// zero. Recall that the zero is our cue to stop.
	while ((p = va_arg(argp, int)) != 0)
		total += p;

	// This frees up any lingering memory associated with the argp variable and
	// helps ensure that we don't have any memory leaks emanating from this
	// function.
	va_end(argp);

	// And finally, return the sum.
	return total;
}
