// COP3502C - Hw#2 SmartArray - Spring 2017 - personal testcase

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"

// QUIT will stop the program once your code has failed
// Put QUIT to 0 if you do not want this to happen or are using diff in Eustis
#define QUIT 1

// **Please note: Flags are guesses as to why your code may have crashed

int main(void)
{
  int i, size, length = -1;
  char *string, buffer[20] = {};
  SmartArray *smarty = NULL;
  FILE *ifp = NULL;

  if((ifp = fopen("names2.txt", "r")) == NULL){
    printf("ERROR: Could not find file name2.txt.\n");
    fflush(stdout);
    exit(0);
  }

  smarty = createSmartArray(length);

  while(fscanf(ifp, "%s", buffer) != EOF)
    put(smarty, buffer);

  if(QUIT){
    if(smarty->capacity != 87 || smarty->size != 50){
      printf("Flag 1: Put function has failed.\n");
      exit(0);
    }
  }

  for(i = 0; i < smarty->size; i += 5){
    string = get(smarty, i);
    printf("Index[%d] = %s.\n", i, string);
  }

  if(QUIT){
    if(strcmp(string, "Colene") != 0){
      printf("Flag 2: Get function has failed.\n");
      exit(0);
    }
  }

  for(i = 0; i < smarty->capacity; i += 5){
    string = get(smarty, i);
    printf("Index[%d] = %s.\n", i, string);
  }

  if(QUIT){
    if(string != NULL){
      printf("Flag 3: ExpandSmartArray function has failed.\n");
      exit(0);
    }
  }

  printf("OH NOOOO! Our data has been hacked!\n");
  for(i = 1; i < smarty->size; i += 3)
    set(smarty, i, "Haxxed");

  printSmartArray(smarty);

  if(QUIT){
    if(strcmp(smarty->array[40], "Haxxed") != 0){
      printf("Flag 4: Set function has failed.\n");
      exit(0);
    }
  }

  smarty = trimSmartArray(smarty);

  if(QUIT){
    if(smarty->size != smarty->capacity || smarty->size != 50){
      printf("Flag 5: trimSmartArray function has failed.\n");
      exit(0);
    }
  }

  printf("Lets clear out this haxxor's strings.\n");
  for(i = 49; i > 0; i -= 3)
    removeElement(smarty, i);

  printSmartArray(smarty);

  if(QUIT){
    if((strcmp(smarty->array[2], "Sunni") != 0) || smarty->size != 33){
      printf("Flag 6: removeElement function has failed.\n");
      exit(0);
    }
  }

  size = getSize(smarty);
  smarty = trimSmartArray(smarty);

  if(QUIT){
    if(size != smarty->capacity || smarty->size != 33){
      printf("Flag 7: getSize function has failed.\n");
      exit(0);
    }
  }

  printf("Luckily we backed up our files.\n");
  rewind(ifp);
  i = 0;
  while(fscanf(ifp, "%s", buffer) != EOF){
    if((i % 3) == 1)
      string = insertElement(smarty, i, buffer);
    i++;
  }

  printSmartArray(smarty);

  if(QUIT){
    if(strcmp(smarty->array[49], "Michal") != 0){
      printf("Flag 8: insertElement function has failed.\n");
      exit(0);
    }
  }

  smarty = destroySmartArray(smarty);

  if(QUIT){
    if(smarty != NULL){
      printf("Flag 9: destroySmartArray function has failed.\n");
      exit(0);
    }
  }

  printf("Congratz! This is the finish line!\n");

  return 0;
}
