// John Yang
// NID: jo886471
// COP 3502, Spring 2017

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Fibonacci.h"

// ========================================================================
// This function adds two integers in HugeInteger format and returns
// the sum as a HugeInteger.
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
  HugeInteger *new_num = malloc(sizeof(HugeInteger));
  int i, min_len, max_len, temp, flag;

	if(p == NULL || q == NULL || new_num == NULL)
		return NULL;

  // This chunk of code checks to see which integer array to use as a guide
  // for looping purposes.
  if(p->length >= q->length)
  {
    flag = 1;
    min_len = q->length; max_len = p->length;
  }
  else
  {
    flag = 2;
    min_len = p->length; max_len = q->length;
  }

  new_num->digits = calloc(max_len + 1, sizeof(int));

  if(new_num->digits == NULL)
    return NULL;

  // This loop begins the addition process.
  // If the two integers being added are the same length, this loop
  // will complete the addition process.
  for(i = 0; i < min_len; i++)
  {
    temp = 0;
    temp = p->digits[i] + q->digits[i];
    if(temp == 9 && new_num->digits[i] == 1)
    {
      new_num->digits[i] = 0; new_num->digits[i+1] = 1;
    }
    else if(temp < 10)
    {
      new_num->digits[i] += temp;
    }
    else
    {
      new_num->digits[i] += (temp - 10); new_num->digits[i+1] = 1;
    }
  }

  // For integers of different lengths, this loop will account
  // for the digits remaining in the longer integer.
  for( ; i < max_len; i++)
  {
    temp = 0;
    if(flag == 1)
      temp = p->digits[i] + new_num->digits[i];
    else
      temp = q->digits[i] + new_num->digits[i];
    if(temp < 10)
      new_num->digits[i] = temp;
    else
      {
        new_num->digits[i] = (temp - 10); new_num->digits[i+1] = 1;
      }
  }

  // Check to see if a '1' was carried over in the last addition operation.
  // Update the length of the sum.
  if(new_num->digits[i] == 1)
    new_num->length = i + 1;
  else
    new_num->length = i;

  return new_num;
}
// ========================================================================
// Frees all memory associated with a HugeInteger stuct.
HugeInteger *hugeDestroyer(HugeInteger *p)
{
  if(p == NULL)
    return NULL;

  free(p->digits);
  free(p);
  p = NULL;

  return NULL;
}
// ========================================================================
// This function takes a string with characters '0' through '9' and converts
// it into an integer in the HugeInteger format.
HugeInteger *parseString(char *str)
{
  HugeInteger *p;
  int len, i;

  if(str == NULL)
    return NULL;

  p = malloc(sizeof(HugeInteger));
  if(p == NULL)
      return NULL;

  // Store the length of the string in "len".  This line is placed after the
  // NULL checkpoint above because if we use strlen() when str = NULL
  // we will segfault.
  len = strlen(str);

  // If the string is empty (""), return the integer zero in HugeInteger format.
  if(len == 0)
  {
    p->digits = calloc(1, sizeof(int));
    if(p->digits == NULL)
      return NULL;
    p->length = 1;
    return p;
  }

  // Allocate the appropriate amount of space for the digits and initialize
  // p->length.
  p->digits = calloc(len, sizeof(int));
  if(p->digits == NULL)
    return NULL;
  p->length = len;

  // Loop through the string, convert each character to an integer
  // and stick it into p->digits in reverse order.
  for(i = len - 1; i >= 0; i--)
    p->digits[len - 1 - i] = str[i] - 48;

  return p;
}

// ========================================================================
// This function takes an unsigned integer and converts it to HugeInteger
// format.
HugeInteger *parseInt(unsigned int n)
{
  int Pow = 10, digitCtr = 2, i;
  HugeInteger *p = malloc (sizeof(HugeInteger));

  if(p == NULL)
    return NULL;

  // We initialize length to 0 until we know what its value should be.
  p->length = 0;

  // If the unsigned int is less than ten, we stick it in a HugeInteger struct
  // and ship it out straight away.
  if(n < 10)
  {
    p->digits = calloc(1, sizeof(int));
    if(p->digits == NULL)
      return NULL;
    p->digits[0] = n;
    p->length = 1;
    return p;
  }

  // This while-loop will loop until "Pow" has the same order of magnitude
  // as n. digitCtr counts the number of digits that n has, or the length of n.
  while(n/10 >= Pow)
  {
    Pow *= 10;
    digitCtr++;
  }

  // Create an integer array of appropriate length here and update
  // p->length to the appropriate value.
  p->digits = calloc(digitCtr, sizeof(int));
  if(p->digits == NULL)
    return NULL;
  p->length = digitCtr;

  // Peel the number down layer by layer (...1000th, 100th, 10th, etc),
  // adding each digit to its appropriate place in p->digits, in reverse order.
  for(i = digitCtr - 1; i > 0; i--)
  {
    p->digits[i] = n/Pow;
    n = n - (p->digits[i] * Pow);
    Pow /= 10;
  }

  // Finally we add the last digit in the 'ones' position.
  p->digits[i] = n;

  return p;
}
// ========================================================================
// This function will take an array of integers from the HugeInteger struct
// and convert that array to an unsigned integer unless it's too big.
unsigned int *toUnsignedInt(HugeInteger *p)
{
  int i, Pow = 1 ;
  unsigned int *total;

  if(p == NULL || p->length > 10)
    return NULL;

  total = calloc(1, sizeof(unsigned int));
  if(total == NULL)
      return NULL;

  // Check if the integer is too large to convert to unsigned int.
  if(p->length == 10)
    if(p->digits[9] > 4)
      return NULL;

  // We take each digit one-by-one from p->digit, amplify it by its respective
  // magnitude and add it to the "total".
  for(i = 0; i < p->length; i++)
  {
    total[0] += (p->digits[i] * Pow);
    Pow *= 10;

    // If we are growing dangerously close to our UINT_MAX value,
    // this chunk of code ensures that we don't breach the threshhold.
    if(i == 8 && p->length == 10)
    {
      if(total[0] > 294967295 && p->digits[9] == 4)
        return NULL;
    }
  }

  return total;
}
// ========================================================================
// This function simply computes fibonacci numbers.
HugeInteger *fib(int n)
{
  // n_2 and n_1 represent the (n-2) and (n-1) values, respectively,
  // in our Fibonacci calculations. n-0 is the value currently
  // being calculated (f(n)).
  HugeInteger *n_2 = NULL, *n_1 = NULL, *n_0 = NULL, *temp = NULL;
  int i;

  if(n < 0)
    return NULL;

  // This creates our n_2, and n_1 HugeInteger structs.
  n_2 = malloc(sizeof(HugeInteger));
  n_1 = malloc(sizeof(HugeInteger));
  if(n_2 == NULL || n_1 == NULL)
    return NULL;

  n_2->digits = calloc(1, sizeof(int));
  n_1->digits = calloc(1, sizeof(int));
  if(n_2->digits == NULL || n_1->digits == NULL)
    return NULL;

  n_1->digits[0] = 1;
  n_2->length = 1;
  n_1->length = 1;

  if(n == 0)
  {
    hugeDestroyer(n_1);
    return n_2;
  }
  if(n == 1)
  {
    hugeDestroyer(n_2);
    return n_1;
  }

  // This does all of the calculations using the hugeAdd function.
  // The n_2 and n_1 structs are constantly being freed and recycled
  // so that we only ever have two structs in memory to feed to hugeAdd().
  for(i = 2; i <= n; i++)
  {
    // Note that we now create our 3rd HugeInteger struct in memory.
    n_0 = hugeAdd(n_2, n_1);
    if(n_0 == NULL)
      return NULL;

    // Free the F(n-2) value or struct.
    n_2 = hugeDestroyer(n_2);
    n_2 = n_1;
    n_1 = n_0;
    n_0 = NULL;
  }
  // When we exit the for-loop above, we now have 2 structs in memory.
  // the one holding the F(n-1) value and our desired F(n) value.
  // We free the F(n-1) struct (which is now pointed to by n_2); both
  // n_1 and n_2 pointers are set to NULL and we return one struct (n_0).
  n_2 = hugeDestroyer(n_2);
  return n_1;
}
// ========================================================================
double difficultyRating(void)
{
  return 3.8;
}
// ========================================================================
double hoursSpent(void)
{
  return 20.0;
}
