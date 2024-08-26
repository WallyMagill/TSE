/*
 * word.c - see word.h for more information
 *
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************** normalizeWord ****************/
/* see word.h for description */
void
normalizeWord(char* word)
{
  // if NULL return
  if (word == NULL) {
    return;
  }
  for (int i = 0; i < strlen(word); i++) {
    word[i] = tolower(word[i]); // changes letter to lower case
  }
}
