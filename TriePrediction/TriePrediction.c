// John Yang
// NID: jo886471
// COP 3502 Spring 2017

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"

// A few chunks of code were copied and/or modified from Dr. Szumlanski.
// Namely, printTrie() and TrieInsert().


// ===========================================================
// Trie Functions
// ===========================================================
TrieNode *createNode(void)
{
  return calloc(1, sizeof(TrieNode));
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TrieNode *TrieInsert(TrieNode *root, char *str)
{
  int i, index, len = strlen(str);
  TrieNode *wizard;

  if (root == NULL)
    root = createNode();

  // As Szumlanski mentioned in class, the wizard starts at the root
  // node and spells out the string being inserted as he/she jumps
  // from node to node. (The wizard is acting as a temp pointer.)
  wizard = root;

  for (i = 0; i < len; i++)
  {
    if (!isalpha(str[i]))
      continue;

    index = tolower(str[i]) - 'a';

    // Before the wizard can move forward to the next node, (s)he needs to
    // make sure that node actually exists. If not, create it!
    if (wizard->children[index] == NULL)
      wizard->children[index] = createNode();

    // Now the wizard is able to jump forward.
    wizard = wizard->children[index];
  }

  // When we break out of the for-loop, the wizard should be at the terminal
  // node that represents the string we're trying to insert.
  wizard->count++;
  return root;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Helper function called by printTrie()
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0.
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

// ===========================================================
// Required Functions and Auxiliary Functions
// ===========================================================

// Takes a string, strips it of all punctuators and returns it.
char *strip(char *str)
{
  int i, j = 0, len;
  char *nakedString;

  if(str == NULL)
    return NULL;

  len = strlen(str);
  nakedString = malloc(sizeof(char) * (len+1));

  for(i = 0; i < len; i++)
  {
    if(isalpha(str[i]))
      nakedString[j++] = tolower(str[i]);
  }

  nakedString[j] = '\0';
  strcpy(str, nakedString);
  free(nakedString);
  return str;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Required buildTrie() Function.
TrieNode *buildTrie(char *filename)
{
	TrieNode *root = NULL, *temp = NULL;
  int len;
  char c;
	char buffer[MAX_CHARACTERS_PER_WORD + 1];

	FILE *ifp = NULL;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
		return NULL;
	}

	// Insert strings one-by-one into the trie.
	while (fscanf(ifp, "%s", buffer) != EOF)
		root = TrieInsert(root, buffer);

  rewind(ifp);

  // Insert strings one-by-one into subtries.
  while (fscanf(ifp, "%s", buffer) != EOF)
  {
    len = strlen(buffer);
    c = buffer[len -1];

    //printf("in subtrie while loop\n");
    // If the current word is the last word in a sentence, stick it in
    // the subtrie of the previous word and continue on to the next sentence.
    if(c == '.' || c == '?' || c == '!')
    {
      if(temp == NULL)
        continue;
      //printf("end of sentence condition\n");
      temp->subtrie = TrieInsert(temp->subtrie, buffer);
      temp = NULL;
      continue;
    }

    // If temp is NULL, we're looking at a word at the beginning
    // of a sentence, which means there is no subtrie for it to go in.
    // If temp isn't NULL and we made it this far down the while loop, it means
    // we have a subtrie that needs a word.
    if(temp != NULL)
      temp->subtrie = TrieInsert(temp->subtrie, buffer);

    // Set temp equal to the terminal node of current word.
    temp = getNode(root, strip(buffer));
  }

  fclose(ifp);
	return root;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TrieNode *destroyTrie(TrieNode *root)
{
  int i, j;

  if(root == NULL)
    return NULL;

  for(i = 0; i < 26; i++)
  {
    destroyTrie(root->children[i]);
  }

  destroyTrie(root->subtrie);
  free(root);
  return NULL;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TrieNode *getNode(TrieNode *root, char *str)
{
  int i, index, len;
  TrieNode *wizard;

  if(root == NULL || str[0] == '\0')
    return NULL;

  len = strlen(str);

  wizard = root;

  for(i = 0; i < len; i++)
  {
    index = tolower(str[i] - 'a');

    if(wizard->children[index] == NULL)
      return NULL;

    wizard = wizard->children[index];
  }

  return (wizard->count > 0) ? wizard : NULL;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This auxiliary function takes two strings, compares them to see which one
// comes first alphabetically and returns that one.
// This function is called when we have two words that occur with equal
// frequency.
char *alphaOrder(char *buffer, char *freq)
{
  int i, buffer_len, freq_len, len;

  buffer_len = strlen(buffer);
  freq_len = strlen(freq);

  if(buffer_len >= freq_len)
    len = freq_len;
  else
    len = buffer_len;

  for(i = 0; i < len; i++)
  {
    if((buffer[i] - 'a') < (freq[i] - 'a'))
      return freq = buffer;

    if((buffer[i] - 'a') > (freq[i] - 'a'))
      return freq;
  }

  return (buffer_len > freq_len) ? freq : (freq = buffer);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This is a recursive auxiliary function that is called by
// getMostFrequentWord().  Also uses pass-by-reference techniques.
void maxHelper(TrieNode *root, char *buffer, char *freq, int k, int *count)
{
	int i;

	if (root == NULL)
		return;

  // if we have a count greater than existing max, then we update the count
  // and copy the new most frequently occuring word in freq.
	if (root->count > *count)
  {
		strcpy(freq, buffer);
    *count = root->count;
  }

  // if we have a tie for frequency, we call the alphaOrder() to compare them
  // alphabetically.
  else if(root->count >= 1 && root->count == *count)
    freq = alphaOrder(buffer, freq);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		maxHelper(root->children[i], buffer, freq, k + 1, count);
	}

	buffer[k] = '\0';
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void getMostFrequentWord(TrieNode *root, char *str)
{
  char *freq, *buffer;
  int k = 0, count = 0;

  if(root == NULL)
  {
    strcpy(str,"");
    return;
  }

  str[0] = '\0';
  freq = malloc(sizeof(char) * (MAX_CHARACTERS_PER_WORD + 1));
  buffer = malloc(sizeof(char) * (MAX_CHARACTERS_PER_WORD + 1));

  maxHelper(root, buffer, freq, k, &count);

  strcpy(str, freq);
  free(freq);
  free(buffer);
  return;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Recursive helper function for continsWord()
int containHelper(TrieNode *root, char *str)
{
  if(root == NULL || str == NULL)
    return 0;

  if(str[0] == '\0')
    if(root->count > 0)
      return 1;

  return containHelper(root->children[str[0] - 'a'], str + 1);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int containsWord(TrieNode *root, char *str)
{
  int flag;
  if(root == NULL || str == NULL)
    return 0;

  char *tempStr = malloc(sizeof(char) * (MAX_CHARACTERS_PER_WORD + 1));
  strcpy(tempStr, str);

  tempStr = strip(tempStr);

  flag = containHelper(root, tempStr);
  free(tempStr);
  return flag;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Recursive helper file to be called by prefixCount().
// It checks to see if the prefix itself exists in the trie,
// and counts how many words we have that begin with this prefix.
// returns the final count to prefixCount().
int prefixHelper(TrieNode *root)
{
  int i, count = 0;
  if (root == NULL)
		return 0;

	if (root->count > 0)
		count += root->count;

	for (i = 0; i < 26; i++)
	{
		count += prefixHelper(root->children[i]);
	}

	return count;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int prefixCount(TrieNode *root, char *str)
{
  int i, len, index;
  TrieNode *wizard;
  char *tempStr = malloc(sizeof(char) * (MAX_CHARACTERS_PER_WORD + 1));

  // if we have an empty tree, or a non-existant string,
  // then no prefixes can be found.
  if(root == NULL || str == NULL)
    {
    free(tempStr);
    return 0;
    }

  // due to the nature of my my strip function, I have to do a little extra
  // work with temporary strings.  I have a lot of other work to do for finals
  // so i didn't take the time to go back and we work my functions.
  // I will do so, as an intellectual exercise once exams are done.
  strcpy(tempStr, str);

  tempStr = strip(tempStr);
  len = strlen(tempStr);
  wizard = root;

  // We take the prefix string and we work out way down to make sure
  // it even exists in out trie.  If it does, we call our helper function to
  // get us the count we're looking for.
  for(i = 0; i < len; i++)
  {
    index = tolower(tempStr[i]) - 'a';

    if(wizard->children[index] == NULL)
    {
      free(tempStr);
      return 0;
    }

    wizard = wizard->children[index];
  }

  free(tempStr);
  return prefixHelper(wizard);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This function handles all of the commands from the input file.
// Once the corpus has been translated into a trie, this function scans the
// input file for instructions and takes the root to the trie.
void inputReader(char *filename, TrieNode *root)
{
  int i, n;
  TrieNode *temp;
  char buffer[MAX_CHARACTERS_PER_WORD + 1], str[MAX_CHARACTERS_PER_WORD + 1];


  FILE *ifp = NULL;

  if((ifp = fopen(filename, "r")) == NULL)
  {
    fprintf(stderr, "Failed to open \"%s\" in inputReader().\n", filename);
    return;
  }

  // Begin scanning for commands
  while(fscanf(ifp, "%s", buffer) != EOF)
  {

    // If the command is '!', print the trie.
    if(!strcmp(buffer, "!"))
    {
      printTrie(root, 0);
    }

    // Otherwise if the command begins with '@', scan in the string
    // that follows and the integer.
    else if(!strcmp(buffer, "@"))
    {
      fscanf(ifp, "%s", buffer);
      fscanf(ifp, "%d", &n);

      // If the trie doesn't contain the string, print the string as it
      // appeared in the input file and move onto the next line in the file.
      if(!containsWord(root, buffer))
      {
        printf("%s\n", buffer);
        continue;
      }

      // If the string exists in the trie, print the string as it appeared in
      // the input file and then we strip it and get it ready to use.
      printf("%s", buffer);
      strcpy(str, strip(buffer));

      // This for loop, loops through n times, and prints out a list of
      // the most frequent words that follow the word before it.
      // if the word is never followed by another word in the corpus
      // (doesn't have a subtrie), we terminate the list early.
      for(i = 0; i < n; i++)
      {
        temp = getNode(root, str);
        if(temp->subtrie == NULL)
          break;
        getMostFrequentWord(temp->subtrie, str);
        printf(" %s", str);
      }
      printf("\n");
    }

    // If the command is just a string, we print it out as it appears in the
    // file and print its subtrie if it exists.
    else
    {
      printf("%s\n", buffer);

      if(containsWord(root, buffer))
      {
        temp = getNode(root, strip(buffer));

        if(temp->subtrie == NULL)
          printf("(EMPTY)\n");
        else
          printTrie(temp->subtrie, 1);
      }
      else
        printf("(INVALID STRING)\n");
    }
  }

  fclose(ifp);
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double difficultyRating(void)
{
  return 4.0;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double hoursSpent(void)
{
  return 20.0;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main(int argc, char **argv)
{
  TrieNode *root;

  root = buildTrie(argv[1]);

  inputReader(argv[2], root);

  root = destroyTrie(root);

  return 0;
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// The End
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
