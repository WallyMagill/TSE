/*
 * index.c - see index.h for more information
 *
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

/**************** global variable ****************/
typedef hashtable_t index_t;

/**************** functions ****************/

/**************** local functions ****************/
/* not visible outside this file */
static void itemdelete(void* item);
static void display_word(void* fp, const char* key, void* item);
static void display_pairs(void* fp, const int key, int count);

/**************** index_new ****************/
/* see index.h for description */
index_t*
index_new(int slots)
{
  return (index_t*) hashtable_new(slots);
}

/**************** index_find ****************/
/* see index.h for description */
void*
index_find(index_t* index, char* key)
{
  return (index_t*) hashtable_find(index, key);
}

/**************** index_insert ****************/
/* see index.h for description */
bool
index_insert(index_t* index, char* key, void* item)
{
  return (index_t*) hashtable_insert(index, key, item);
}

/**************** index_delete ****************/
/* see index.h for description */
void
index_delete(index_t* index)
{
  hashtable_delete(index, itemdelete);
}

/**************** index_save ****************/
/* see index.h for description */
void
index_save(index_t* index, FILE* fp)
{
  hashtable_iterate(index, fp, display_word);
}

/**************** index_load ****************/
/* see index.h for description */
void
index_load(index_t* index, FILE* fp)
{
  // initalize counters
  counters_t* counters;
  // initalize variables
  char* word;
  int id;
  int count;
  // cycles through file
  while (!feof(fp)) {
    word = file_readWord(fp); // gets word on line
    if (word != NULL) {
      // scans through id and counnt after word
      while((fscanf(fp, " %d %d", &id, &count)) == 2) {
        // checks for word if not in index creates new counter and inserts
        if ((counters = index_find(index, word)) == NULL) {
          counters = counters_new();
          counters_set(counters, id, count);
          index_insert(index, word, counters);
        } else {
          // sets counter for id
          counters_set(counters, id, count);
        }
      }
    }
    free(word);
  }
}

/**************** helper functions ****************/
/* not visible outside this file */

/**************** itemdelete ****************/
/* Helps delete the counters in the hashtable */
static void
itemdelete(void* item)
{
  counters_delete((counters_t*)item);
}

/**************** display_word ****************/
/* Prints word to file then iterates through counters */
static void
display_word(void* fp, const char* key, void* item)
{
  fprintf(fp, "%s", key); // prints the word to file
  counters_iterate(item, fp, display_pairs);
  fprintf(fp, "\n"); // goes to next line
}

/**************** display_pairs ****************/
/* Prints pairs to file */
static void
display_pairs(void* fp, const int key, int count)
{
  fprintf((FILE*) fp, " %d %d", key, count); // prints pairs in counters to file
}
