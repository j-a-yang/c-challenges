// John A. Yang
// NID: jo886471
// COP 3502, Spring 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"

// ===========================================================================
// This function creates a smart array.
SmartArray *createSmartArray(int length)
{
  SmartArray *smarty;
  int i, Max;
  smarty = malloc(sizeof(SmartArray));
  if(smarty == NULL)
    return NULL;

  // Set the length of the array to desired length or to 10 if the desired
  // length is less than 10.
  if(length > DEFAULT_INIT_LEN)
    Max = length;
  else
    Max = DEFAULT_INIT_LEN;

  // Dynamically allocate memory of appropriate size for the array.
  smarty->array = malloc(sizeof(char*) * Max);
  if(smarty->array == NULL)
    return NULL;

  // Set all new array positions to NULL and intitialize capacity and size.
  for(i = 0; i < Max; i++)
    smarty->array[i] = NULL;
  smarty->capacity = Max;
  smarty->size = 0;

  // Print statement indicating the size of the new array created.
  printf("-> Created new SmartArray of size %d.\n", smarty->capacity);

  return smarty;
}

// ===========================================================================
// This function clears all memory associated with the SmartArray.
SmartArray *destroySmartArray(SmartArray *smarty)
{
  int i;

  if(smarty == NULL)
    return NULL;

  // Free each string in the array, then free the array, then free the struct.
  for(i = 0; i < smarty->capacity; i++)
    free(smarty->array[i]);
  free(smarty->array);
  free(smarty);

  // Set smarty to NULL just in case the returned
  // NULL is not returned to the correct struct pointer.
  smarty = NULL;
  return NULL;
}

// ===========================================================================
// This function increases the capacity of an array to a desired length.
SmartArray *expandSmartArray(SmartArray *smarty, int length)
{
  int i;
  char** temp;

  if(smarty == NULL)
    return smarty;
  if(length <= smarty->capacity)
    return smarty;

  // Dynamically allocate memory for a new array to desired length and
  // store the address in as a temporary variable.
  temp = malloc(sizeof(char*) * length);
  if(temp == NULL)
    return NULL;

  // Copy the contents of the old array into the new array and set the new
  // array elements to NULL.
  for(i = 0; i < smarty->capacity; i++)
    temp[i] = smarty->array[i];
  for(i = smarty->capacity; i < length; i++)
    temp[i] = NULL;

  // Free the old array, store the address of the new array, and update the
  // capacity of the array to the new length.
  free(smarty->array);
  smarty->array = temp;
  smarty->capacity = length;

  // Print statement indicating the new updated size of the array.
  printf("-> Expanded SmartArray to size %d.\n", smarty->capacity);

  return smarty;
}

// ===========================================================================
// This function trims an array to the exact size of the array so that there
// are no empty elements in the array.
SmartArray *trimSmartArray(SmartArray *smarty)
{
  int i;
  char** temp;

  if(smarty == NULL)
    return NULL;
  if(smarty->size == smarty->capacity)
    return smarty;

  // Dynamically allocate memory for a new array that is just big enough to
  // store only the active elemets of the old array.
  // Also, store the address of the new array in "temp".
  temp = malloc(sizeof(char*) * (smarty->size));
  if(temp == NULL)
    return NULL;

  // Copy only the active elements of the old array to the new array.
  for(i = 0; i < smarty->size; i++)
    temp[i] = smarty->array[i];

  // Free the old array and store the memory address of the new array.  Update
  // the capacity of the struct, which should now equal the number of active
  // elements (size) of the array.
  free(smarty->array);
  smarty->array = temp;
  smarty->capacity = smarty->size;

  // Print statement indicating the new length of the array.
  printf("-> Trimmed SmartArray to size %d.\n", smarty->size);

  return smarty;
}

// ============================================================================
// This funtion adds a string to the next available element in the smart array.
char *put(SmartArray *smarty, char *str)
{

  if(smarty == NULL || str == NULL)
    return NULL;

  // If there are now empty array elements available, expand the array
  // to double the size plus one.
  if(smarty->capacity == smarty->size)
    expandSmartArray(smarty, (smarty->capacity * 2 + 1));

  // Dynamically allocate memory large enough to hold the new string, plus
  // null sentinel, and store the memory address of this new string in the
  // first empty array element.
  smarty->array[smarty->size] = malloc(sizeof(char) * strlen(str) + 1);
  if(smarty->array[smarty->size] == NULL)
    return NULL;

  // Copy the characters from the input string into the string we just created
  // and update the size of our array.
  strcpy(smarty->array[smarty->size], str);
  smarty->size++;

  // Return the string we just created.
  return smarty->array[smarty->size-1];
}

// ============================================================================
// This function attempts to retrieve a string from the given index
// of our array.
char *get(SmartArray *smarty, int index)
{
  // If the index is out of bounds of our array, we will return NULL.
  if(smarty == NULL || index > smarty->capacity - 1 || index < 0)
    return NULL;

  // If the index is valid, we will return the contents of that index
  // in our array.
  return smarty->array[index];
}

// ===========================================================================
// This function replaces an existing string in our array with a new one.
char *set(SmartArray *smarty, int index, char *str)
{
  char *temp;

  if(smarty == NULL || str == NULL)
    return NULL;

  // Protects against the index being out of bounds of the array.
  if(index > smarty->capacity - 1 || index < 0)
    return NULL;

  if(smarty->array[index] == NULL)
    return NULL;

  // Dynamically allocate memory for the new string and temporarily hold the
  // address in "temp".
  temp = malloc(sizeof(char) * strlen(str) + 1);
  if(temp == NULL)
    return NULL;

  // Copy the characters of the input string into the newly created string,
  // then free the old array element and replace it with the new string.
  strcpy(temp, str);
  free(smarty->array[index]);
  smarty->array[index] = temp;

  // Return the new string.
  return smarty->array[index];
}

// ===========================================================================
//This function inserts a new string into our array and shift all of the
//elements in the array up one.
char *insertElement(SmartArray *smarty, int index, char *str)
{
  int i;
  char *temp;

  if(smarty == NULL || str == NULL)
    return NULL;

  // If the array is full, expand the array to double the size plus one.
  if(smarty->capacity == smarty->size)
    expandSmartArray(smarty, (smarty->capacity * 2 + 1));

  // Protects against the index being out of bounds of the array.
  if(index > smarty->capacity - 1 || index < 0)
    return NULL;

  // Dynamically allocate memory for the sting and hold the address in "temp".
  // Then copy the characters into the new string.
  temp = malloc(sizeof(char) * strlen(str) + 1);
  if(temp == NULL)
    return NULL;
  strcpy(temp, str);

  // If the index is bigger than size of the array, add the new string to the
  // next available element in the array.  Otherwise, shift all active elements
  // above the index over by one and insert the new string in the desired index.
  if(index >= smarty->size)
    smarty->array[smarty->size] = temp;
  else{
    for(i = (smarty->size - 1); i >= index; i--)
        smarty->array[i+1] = smarty->array[i];
    smarty->array[index] = temp;
  }

  // Update the size of the array.
  smarty->size++;

  return smarty->array[index];
}

// ============================================================================
// This function goes to an index of our array and clears its contents
// then closes the gap.
int removeElement(SmartArray *smarty, int index)
{
  int i;

  if(smarty == NULL)
    return 0;
  if(index >= smarty->size)
    return 0;

  // Protects against the index being out of bounds of the array.
  if(index > smarty->capacity - 1 || index < 0)
    return NULL;

  // Free the contents of this index in the array.
  free(smarty->array[index]);

  // Shift all active elements the above the index down by one to close
  // the gap.
  for(i = index; i < smarty->size-1; i++)
    smarty->array[i] = smarty->array[i+1];

  // The last element that was previously active, is now empty and needs to be
  // set to NULL, which is accomplished here.
  smarty->array[smarty->size-1] = NULL;
  smarty->size--;
  return 1;
}

// ===========================================================================
// This function retrieves the size of an array.
int getSize(SmartArray *smarty)
{
  if(smarty == NULL)
    return -1;

  // Return the size of this array.
  return smarty->size;
}

// ===========================================================================
// This function prints out the contents of the array.
void printSmartArray(SmartArray *smarty)
{
  int i;

  // If the struct pointer argurment is null or if there is nothing stored in
  // this array print "(empty array)" and exit the function.
  if(smarty == NULL || smarty->size == 0){
    printf("(empty array)\n");
    return;
  }

  // Print each active element of the array.
  for(i = 0; i < smarty->size; i++){
      if(smarty->array[i] == NULL)
        printf("(empty array)\n");
      else
        printf("%s\n",smarty->array[i]);
  }

  return;
}

// ===========================================================================
double difficultyRating(void)
{
  return 4.0;
}
double hoursSpent(void)
{
  return 20.0;
}
