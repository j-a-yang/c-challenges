#include <stdio.h>
#include <string.h>

typedef struct T
{
  int gl;
  char name[5];
} T;

int main(void)
{
  T data;

  data.gl = 597;
  strcpy(data.name, "Vince");

  printf("%s (%d)\n", data.name, data.gl); 

  return 0;
}
