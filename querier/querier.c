/*
 * indexer.c - a program constructed from requirements from CS50 Lab 6
 *
 * This is one part of the TSE project. This module will produce a list
 * of urls and their search score in decending order using a given
 * pageDirectory, index, and valid search query.
 * 
 * Usage: ./querier pageDirectory indexFilename
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
/* Type Structure counters_pair */
typedef struct counters_pair {
  counters_t* firstSet;
  counters_t* secondSet;
} counters_pair_t;
/* Type Structure score */
typedef struct score {
  int docID;
  int score;
} score_t;

/* Initalize all helper functions */
static void validateArgs(int argc, char* argv[]);
static void startQuary (index_t* index, char* pageDirectory);
static char firstNonAlpha(char* input);
static void normalizeInput(char** wordList, char* input, int* wordNum);
static void runQuery(index_t* index, char** wordList, char* pageDirectory, int wordNum);
static bool validateQuery(char** wordList, int wordNum);
static bool isOperator(char* word);
static void printCleanQuery(char** wordList, int wordNum);
static counters_t* counterCreation(index_t* index, char** words, int wordNum);
static void unionizeSets(counters_t* andSet, counters_t* orSet);
static void unionizeSetsHelper(void* arg, const int key, int count);
static void intersectionOfSets(counters_t* orSet, counters_t* temp);
static void intersectionOfSetsHelper(void* arg, const int key, int count);
static void matchCounter(void* arg, const int key, int count);
static int findNumFiles(char* pageDirectory);
static score_t** scoreQueryResults(counters_t* queryCounter, int numOfMatches, int numOfFiles);
static score_t** sortQueryResults(score_t** score_list, int numOfDocs);
static void printQuery(score_t** scoresRanked, char* pageDirectory, int numOfMatches);

/**************** main ****************/
/* Calls all the helper functions and handles arguments
 * 
 * Caller provides:
 *   command line arguments:
 *   pageDirectory - a readable directory created by crawler
 *   indexFilename - a file in which an index is written
 * We return:
 *   zero if ran successfully
 * We do:
 *   call helper functions
 */
int main (int argc, char* argv[])
{
  validateArgs(argc, argv);

  FILE* fp = fopen(argv[2], "r");
  int indexWordNum = file_numLines(fp);
  index_t* index = index_new(indexWordNum);
  
  index_load(index, fp); // creates index from file
  startQuary(index, argv[1]);
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
 *   indexFilename is a readable file
 * We do:
 *   go through all the guarantees exiting if not successful
 *   and printing to stderr
 */
static void
validateArgs(int argc, char* argv[])
{
  // checks for three arguments
  if (argc != 3) {
    fprintf(stderr, "Invalid command-line arguments.\nUsage: ./querier pageDirectory indexFilename\n");
    exit(1);
  }
  // validates pageDirectory
  if (!pagedir_validate(argv[1])) {
    exit(1);
  }
  // checks indexFilename is readable
  FILE* fp;
  if ((fp = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "Invalid indexFilename. The indexfilename can not be read.\n");
    exit(1);
  }
  fclose(fp);
}

/**************** startQuary ****************/
/* Begins the query search by doing prep
 * 
 * Caller provides:
 *   valid index and pageDirectory
 * We garentee:
 *   that the input has valid characters
 * We do:
 *   checks for query input
 */
static void
startQuary (index_t* index, char* pageDirectory)
{
  printf("Query? "); // promps user

  char* input = NULL; // input string
  int wordNum = 0; // number of wrods in input
  while ((input = file_readLine(stdin)) != NULL) {
    char result = firstNonAlpha(input);
    // if input has no non alpha characters
    if (result == '\0') {
      // create char** with all normalized words from input
      char* wordList [(strlen(input))/2];
      normalizeInput(wordList, input, &wordNum);
      // runs query
      runQuery(index, wordList, pageDirectory, wordNum);
      free(input);
      printf("\n-----------------------------------------------\nQuary? ");
      wordNum = 0;
    } else {
      // error for bad character and reprompt
      fprintf(stderr, "Error: bad character '%c' in query.\n", result);
      free(input);
      printf("\n-----------------------------------------------\nQuary? ");
    }
  }
  free(input);  
}

/**************** runQuery ****************/
/* Runs the serach query on th eindex
 * 
 * Caller provides:
 *   valid index, list of words, pageDirectory 
 *   and the number of words
 * We guarantee:
 *   query is valid
 * We do:
 *   search through the index based on the query
 *   then rank the results desplaying results
 */
static void
runQuery(index_t* index, char** wordList, char* pageDirectory, int wordNum)
{
  if (validateQuery(wordList, wordNum)) {
    printCleanQuery(wordList, wordNum); // prints out normalize query
    counters_t* queryCounter = counterCreation(index, wordList, wordNum); // creates counter with query results
    // finds the number of matches
    int numOfMatches = 0;
    counters_iterate(queryCounter, &numOfMatches, matchCounter);
    // if no matches print error
    if (numOfMatches == 0) {
      printf("No documents match.\n");
    } else {                                                                                                                                            
      printf("Matches %d documents (ranked):\n", numOfMatches); // prints heading
      int numOfFiles = findNumFiles(pageDirectory);
      // create list of scores and sorts
      score_t** listOfScores = scoreQueryResults(queryCounter, numOfMatches, numOfFiles);
      score_t** sortedScores = sortQueryResults(listOfScores, numOfMatches);
      // prints scores
      printQuery(sortedScores, pageDirectory, numOfMatches);
      // cycle through and free
      for (int i = 0; i < numOfMatches; i++) {
        free(sortedScores[i]);
      }
      free(sortedScores);
    }
    counters_delete(queryCounter);
  }
}

/**************** firstNonAlpha ****************/
/* Gives the first non alpha character in the input
 * 
 * Caller provides:
 *   an input string
 * We return:
 *   the non alpha character or NULL
 * We guarantee:
 *   all the characters in input are either alpha
 *   or space (with varients)
 */
static char
firstNonAlpha(char* input) 
{
  int i = 0;
  while (input[i] != '\0') {
    // checks if not space or alpha
    if (!isalpha(input[i]) && !isspace(input[i])) {
        return input[i]; // returns bad character
    }
    i++;
  }
  return '\0'; // returns null
}

/**************** normalizeInput ****************/
/* Creates a char** of all the normailzed words from input
 * 
 * Caller provides:
 *   valid char** list of words, input string, and number 
 *   of words
 * We guarantee:
 *   that all words in list are normalized
 * We do:
 *   nomalize the words as well as increase word number
 *   each time a word is added to the list
 */
static void
normalizeInput(char** wordList, char* input, int* wordNum)
{
  const char* delimiter = " \t\n"; // delimiter for strtok
  char* word = strtok(input, delimiter);
  // normalizes every word and stores in wordList
  while (word != NULL) {
    normalizeWord(word);
    wordList[(*wordNum)++] = word;
    word = strtok(NULL, delimiter);
  }
}

/**************** validateQuery ****************/
/* Given the list of words, checks them
 * 
 * Caller provides:
 *   argc and argv[]
 * We return:
 *   if we are successful we return true if not then 
 *   return false and print error
 * We guarantee:
 *   word number is not 0
 *   that the first word is not an operator
 *   that the last word is not an operator
 *   no operators are adjacent
 */
static bool
validateQuery(char** wordList, int wordNum)
{
  // checks for words in query
  if (wordNum == 0) {
    return false;
  }
  // checks if first word is operator
  if (isOperator(wordList[0])) {
    printCleanQuery(wordList, wordNum);
    fprintf(stderr, "Error: '%s' cannot be first\n", wordList[0]);
    return false;
  }
  // checks if last word is operator
  if (isOperator(wordList[wordNum - 1])) {
    printCleanQuery(wordList, wordNum);
    fprintf(stderr, "Error: '%s' cannot be last\n", wordList[wordNum - 1]);
    return false;
  }
  // checks that no two operators are adjacent
  for (int i = 1; i < wordNum - 1; i++) {
    if (isOperator(wordList[i]) && isOperator(wordList[i + 1])) {
      printCleanQuery(wordList, wordNum);
      fprintf(stderr, "Error: '%s' and '%s' cannot be adjacent\n", wordList[i], wordList[i + 1]);
      return false; 
    }
  }
  return true;
}

/**************** isOperator ****************/
/* Given a word checks if its an operator
 * 
 * Caller provides:
 *   a string (word)
 * We return:
 *   if we are successful we return true if not 
 *   then return false
 * We guarantee:
 *   the word is not equal to "and" or "or"
 */
static bool
isOperator(char* word)
{
  // checks if word is "and" or "or"
  if (strcmp(word, "and") != 0 && strcmp(word, "or") != 0) {
    return false;
  }
  return true;
}

/**************** printCleanQuery ****************/
/* Prints the normalized query
 * 
 * Caller provides:
 *   valid word list and word number
 * We do:
 *   print header then cycle through word list 
 *   printing normalized words
 */
static void
printCleanQuery(char** wordList, int wordNum)
{
  printf("Query:");
  // cycles through the list of normalized words
  for (int i = 0; i < wordNum; i++) {
    printf(" %s", wordList[i]);
  }
  printf("\n");
}

/**************** counterCreation ****************/
/* Creates a counter with results from query
 * 
 * Caller provides:
 *   valid index, list of words, and number of words
 * We return:
 *   A counter with query results
 * We do:
 *   navigate through different operators allowing
 *   for the unionizing and intersecting of sets
 *   to create results
 */
static counters_t*
counterCreation(index_t* index, char** wordList, int wordNum)
{
  // set trigger and create "and" and "or" set
  bool trigger = false;
  counters_t* andSet = counters_new();
  counters_t* orSet = counters_new();
  // cycles through word list
  for (int i = 0; i < wordNum; i++) {
    // checks for "or"
    if (strcmp(wordList[i], "or") == 0) {
      unionizeSets(orSet, andSet); // unionizes to andSet
      // delete andSet and recreate
      counters_delete(andSet);
      andSet = counters_new();
      trigger = false;
      continue;
    // check for "and"
    } else if (strcmp(wordList[i], "and") == 0) {
      trigger = true; // set trigger for and
      continue;
    } else {
      counters_t* temp = index_find(index, wordList[i]);
      if (!trigger) {
        // runs unionize for first time and "or"
        unionizeSets(andSet, temp);
        trigger = true; // trigger default
      } else {
        // runs interesection for "and"
        intersectionOfSets(andSet, temp);
        trigger = true; // trigger default
      }
    }
  }
  // unionizes sets, deletes unessesary set, and returns
  unionizeSets(orSet, andSet);
  counters_delete(andSet);
  return orSet;
}

/**************** unionizeSets ****************/
/* Unionizes two sets
 * 
 * Caller provides:
 *   two valid counters
 * We do:
 *   create a counters_pair and itterate through
 *   counters
 */
static void
unionizeSets(counters_t* andSet, counters_t* orSet)
{
  // creates counters_pair and iterates
  counters_pair_t counters_pair = {andSet, orSet};
  counters_iterate(orSet, &counters_pair, unionizeSetsHelper);
}

/**************** unionizeSetsHelper ****************/
/* Helper function for unionizing sets
 * 
 * We do:
 *   combines the sets together and adds the count if
 *   both sets have the same document
 */
static void
unionizeSetsHelper(void* arg, const int key, int count)
{
  counters_pair_t* counters_pair = arg;
  // gets sum and sets
  int countSum = counters_get(counters_pair->firstSet, key) + counters_get(counters_pair->secondSet, key);
  counters_set(counters_pair->firstSet, key, countSum);
}

/**************** intersectionOfSets ****************/
/* Unionizes two sets
 * 
 * Caller provides:
 *   two valid counters
 * We do:
 *   create a counters_pair and itterate through
 *   counters
 */
static void
intersectionOfSets(counters_t* orSet, counters_t* temp)
{
  // creates counters_pair and iterates
  counters_pair_t counters_pair = {orSet, temp};
  counters_iterate(orSet, &counters_pair, intersectionOfSetsHelper);
}

/**************** intersectionOfSetsHelper ****************/
/* Helper function for intersecting sets
 * 
 * We do:
 *   check to find the minimum score between the two sets
 *   and changes the score in that set
 */
static void
intersectionOfSetsHelper(void* arg, const int key, int count)
{
  counters_pair_t* counters_pair = arg;
  int firstCount = counters_get(counters_pair->firstSet, key);
  int secondCount = counters_get(counters_pair->secondSet, key);
  // checks and sets lower count
  if (secondCount < firstCount) {
    counters_set(counters_pair->firstSet, key, secondCount);
  }
}

/**************** matchCounter ****************/
/* Counts the number of matches for the query
 * 
 * Caller provides:
 *   use for counters_iterate through resulting query
 * We do:
 *   check if count is greater then 0 and increments
 *   the number of matches
 */
static void
matchCounter(void* arg, const int key, int count) 
{
  int* numOfMatches = arg;
  if (count > 0) {
    (*numOfMatches)++;
  }
}

/**************** findNumFiles ****************/
/* Finds the number of files in a given pageDirectory
 * 
 * Caller provides:
 *   valid pageDirectory
 * We return:
 *   an integer of number of files in pageDirectory
 * We do:
 *   cycle through the files in pageDirectory starting
 *   at 1 and incrementing a count
 */
static int
findNumFiles(char* pageDirectory)
{
  // initalize variables
  FILE* fp;
  int count = 0;
  int docID = 1;
  char* filename = (char*)mem_malloc(strlen(pageDirectory) + 12);
  // create path name and cycle through docID
  sprintf(filename, "%s/%d", pageDirectory, docID);
  while ((fp = fopen(filename, "r")) != NULL) {
    count++;
    docID++;
    fclose(fp);
    sprintf(filename, "%s/%d", pageDirectory, docID);
  }
  mem_free(filename);
  return count;
}

/**************** score ****************/
/* Given a counter with results creates a score_t**
 * that contains all documents and scores in an array
 * 
 * Caller provides:
 *   valid counters, number of mathces, and number of
 *   files
 * We return:
 *   an array of score_t 
 * We do:
 *   go through the counter creating score_t if count
 *   is greater then 0 and adding them to array
 */
static score_t**
scoreQueryResults(counters_t* queryCounter, int numOfMatches, int numOfFiles)
{
  // initalize 
  score_t** score_list = mem_calloc(numOfMatches, sizeof(score_t));
  // cycles through all possible files
  int count = 0;
  for (int i = 1; i <= numOfFiles; i++) {
    // checks for score
    int scoreForDoc = counters_get(queryCounter, i);
    // if score exist
    if (scoreForDoc > 0) {
      // creates score and initalizes
      score_t* temp_score = mem_malloc(sizeof(score_t));
      temp_score->docID = i;
      temp_score->score = scoreForDoc;
      // adds score to list of scores
      score_list[count] = temp_score;
      count++;
    }
  }
  return score_list;
}

/**************** sort ****************/
/* Given a list of scores sorts them into an array
 * 
 * Caller provides:
 *   valid score_t** and number of docs
 * We return:
 *   a sorted array of score_t 
 * We do:
 *   cycle through all the scores swapping them to
 *   sort the array
 */
static score_t**
sortQueryResults(score_t** score_list, int numOfDocs)
{
  // cycles through scores comparing and organizing
  for (int i = 0; i < (numOfDocs-1); i++) {
    for (int j = i+1; j < numOfDocs; j++) {
      if (score_list[i]->score < score_list[j]->score) {
        score_t* temp_score = score_list[i]; // for storing for swap
        // swap the scores
        score_list[i] = score_list[j];
        score_list[j] = temp_score;
      }
    }
  }
  return score_list;
}

/**************** printQuery ****************/
/* Given the ranked scores prints the resutls
 * 
 * Caller provides:
 *   valid ranked scores, pageDirectory, and number of mathces
 * We do:
 *   cycle through the ranked scores printing the scor,
 *   docID, and the url for the website
 */
static void
printQuery(score_t** scoresRanked, char* pageDirectory, int numOfMatches)
{
  FILE* fp;
  // cycles through matches
  for (int i = 0; i < numOfMatches; i++) {
    // creates filename
    char filename [strlen(pageDirectory) + 12];
    sprintf (filename, "%s/%d", pageDirectory, scoresRanked[i]->docID);
    // get url from file
    fp = fopen (filename, "r");
    char* url = file_readLine(fp);
    // prints then preps for loop
    printf ("Score: %d doc: %d: %s\n", scoresRanked[i]->score, scoresRanked[i]->docID, url);
    free(url);
    fclose(fp);
  }
}
