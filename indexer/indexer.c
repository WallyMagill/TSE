/*
 * indexer.c - a program constructed from requirements from CS50 Lab 5
 *
 * This is one part of the TSE project. It is intended to index words 
 * with file ids and counts for times appeared.
 * 
 * Usage: ./indexer pageDirectory indexFilename
 * Further information on inputs in main.
 * 
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "../common/index.h"
#include "../common/word.h"
#include "../common/pagedir.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"

/* Initalize all helper functions */
static void validateArgs(int argc, char* argv[]);
static index_t* indexBuild(char* pageDirectory);
static void indexPage(index_t* index, webpage_t* webpage, int id);

/**************** main ****************/
/* Calls all the helper functions and handles arguments
 * 
 * Caller provides:
 *   command line arguments:
 *   pageDirectory - a readable directory created by crawler
 *   indexFilename - a file in which to write the index
 * We return:
 *   zero if ran successfully
 * We do:
 *   call helper functions
 */
int
main(int argc, char* argv[])
{
  validateArgs(argc, argv); // checks all arguments are valid
  // construct types
  index_t* index = indexBuild(argv[1]);
  FILE* fp =  fopen(argv[2], "w");
  // saves index to file
  index_save(index, fp);
  // delete and close index
  index_delete(index);
  fclose(fp);
  return 0;
}

/**************** validateArgs ****************/
/* Given arguments from the command line, checks them
 * 
 * Caller provides:
 *   argc and argv[]
 * We return:
 *   if we are successful we return if not then exit non-zero
 * We guarantee:
 *   there are 3 arguments
 *   pageDirectory is valid and created by crawler
 *   indexFilename is a valid writable file
 * We do:
 *   go through all the guarantees exiting if not successful
 *   and printing to stderr
 */
static void
validateArgs(int argc, char* argv[])
{
  // checks for three arguments
  if (argc != 3) {
    fprintf(stderr, "Invalid command-line arguments.\nUsage: ./indexer pageDirectory indexFilename\n");
    exit(1);
  }
  // validates pageDirectory
  if (!pagedir_validate(argv[1])) {
    exit(1);
  }
  // checks indexFilename is writable
  FILE* fp;
  if ((fp = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Invalid indexFilename. The indexfilename can not be written in.\n");
    exit(1);
  }
  fclose(fp);
}

/**************** indexBuild ****************/
/* Construct an index using a directory
 * 
 * Caller provides:
 *   valid directory name
 * We return:
 *   a fully constructed index type
 * We do:
 *   create an index by looping through different files
 *   by opening pageDirectory/1 and then increasing
 *   until NULL. returns built index.
 */
static index_t*
indexBuild(char* pageDirectory)
{
  // initalize type structures
  index_t* index = index_new(550); // reasonable number (between 200-900)
  webpage_t* webpage;
  FILE* fp;
  // creates fileName for first file 'id'
  int id = 1;
  char* fileName = (char*)mem_malloc(strlen(pageDirectory) + 12); // allows up to 10 digit file ids
  sprintf(fileName, "%s/%d", pageDirectory, id);
  // cycles through files starting at '1' and increasing each time
  while ((fp = fopen(fileName, "r")) != NULL) {
    webpage = pagedir_load(fp);
    indexPage(index, webpage, id); 
    // delete and close
    fclose(fp);
    webpage_delete(webpage);
    // construct next fileName for while loop
    id++;
    sprintf(fileName, "%s/%d", pageDirectory, id);
  }
  mem_free(fileName); // free file name when done
  return index;
}

/**************** indexPage ****************/
/* Cycle through words in webpage incrementing
 * counts in the index accourding to file id
 * 
 * Caller provides:
 *   valid index type
 *   valid webpage type
 *   valid id associated with webpage
 * We do:
 *   cycle through the words in the webpage, creating
 *   counters for words and incrementing exsisiting
 *   counters
 */
static void
indexPage(index_t* index, webpage_t* webpage, int id)
{
  // initalize type structures
  counters_t* counters;
  // initalize variables
  int pos = 0;
  char* word;
  // cycles through the words of the webpage
  while ((word = webpage_getNextWord(webpage, &pos)) != NULL) {
    // insures at least three letters
    if (strlen(word) >= 3) {
      normalizeWord(word); // normalizes word
      // looks for counter type for word in hashtable
      counters = index_find(index, word);
      // if counters is NULL create new, add doc id, insert into index
      if (counters == NULL) {
        counters = counters_new();
        counters_add(counters, id);
        index_insert(index, word, counters);
      } else {
        counters_add(counters, id); // increments counter for id
      }
    }
  free(word);
  }
}
