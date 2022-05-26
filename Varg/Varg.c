// John A. Yang
// NID: jo886471
// COP 3502, Spring 2017

#include <stdio.h>
#include <stdarg.h>
#include "Varg.h"


char mostFrequentChar(int n, ...){

  int freq[26], maxfreq =0;
  int i, j, index, maxindex;
  va_list argp;


  if (n == 0)
    return '\0';

  for(j = 0; j<26; j++)
    freq[j]=0;

  va_start(argp, n);

// Keeps a tally of how many of each letter is received by the function.

  for(i = 0; i<n; i++){
    index = va_arg(argp, int) - 'a';
    freq[index]++;

// Checks which letter occurs most frequently, and ensures that
// if there is a tie, the first letter to reach the highest frequency
// is the one that is ultimately returned.

    for(j = 0; j<26; j++){
      if(freq[j] > maxfreq){
          maxfreq = freq[j];
          maxindex = j;
      }
    }
  }

  va_end(argp);

  return maxindex + 'a';
}

char fancyMostFrequentChar(char c, ...){

  int index, maxindex, freq[26];
  int i, p, maxfreq;
  va_list argp;

  if(c == '\0')
    return '\0';

  for(i = 0; i < 26; i++)
    freq[i] = 0;

// If the first character received by the function was not '\0',
// the program will record which character was first received and make
// the first "tally mark" for that character.

  freq[c - 'a']++;
  maxindex = c - 'a';
  maxfreq = 1;

  va_start(argp, c);

// This loop allows the program to take in characters, one by one,
// until it receives a '\0'.  A tally will be kept for each character
// received, while ensuring that the first character to have reached the
// maximum frequency is the one that is returned.

  while((p = va_arg(argp, int)) != '\0'){
    index = p - 'a';
    freq[index]++;

    for(i = 0; i<26; i++){
      if(freq[i] > maxfreq){
          maxfreq = freq[i];
          maxindex = i;
      }
    }
  }

  va_end(argp);

  return maxindex + 'a';
}

double difficultyRating(void){
  return 3.7;
}

double hoursSpent(void){
  return 8.0;
}
