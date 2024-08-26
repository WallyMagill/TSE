/*
 * crawler.c - a program constructed from requirements from CS50 Lab 4
 *
 * This is one part of the TSE project. It is intended to crawl a given 
 * URL until a specified depth extracting the pages inside each URL.
 * 
 * Usage: ./crawler seedURL pageDirectory maxDepth
 * Further information on inputs in main.
 * 
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/mem.h"
#include "../common/pagedir.h"

/* Initalize all helper functions */
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);
static void logr(const char *word, const int depth, const char *url);

/**************** main ****************/
/* Calls all the helper functions and handles arguments
 * 
 * Caller provides:
 *   command line arguments:
 *   seedURL - is an internal normalized URL
 *   pageDirectory - a writable directory
 *   maxDepth - integer in range [0-10]
 * We return:
 *   zero if ran successfully
 * We do:
 *   call helper functions
 */
int 
main(const int argc, char* argv[])
{
  parseArgs(argc, argv, &argv[1], &argv[2], (int*)(argv[3])); // need to make sure arguments are pointers
  crawl(normalizeURL(argv[1]), argv[2], atoi(argv[3])); // need argv[1] to be normalized and argv[3] to be converted to int
  return 0;
}

/**************** parseArgs ****************/
/* Given arguments from the command line, extracts them into 
 * funtion parameters
 * 
 * Caller provides:
 *   argc, argv[], and correct arguments for each slot in 
 *   apropriate format
 * We return:
 *   if we are successful we return if not then exit non-zero
 * We guarantee:
 *   there are 4 arguments
 *   seedURL is normalized and internal
 *   pageDirectory is valid adn initalized
 *   maxDepth is in range [0-10]
 * We do:
 *   go through all the guarantees exiting if not successful
 */
static void 
parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{
  // checks number of arguments
  if (argc != 4) {
    fprintf(stderr, "Wrong number of arguments\nUsage: ./crawler seedURL pageDirectory maxDepth\n");
    exit(1);
  }
  // checks seedURL is normalized and is intternal
  char* normalizedURL = normalizeURL(argv[1]);
  if (!isInternalURL(normalizedURL)) {
    fprintf(stderr, "Normalized seedURL is not internal.\n");
    free(normalizedURL);
    exit(1);
  }
  free(normalizedURL); // free from normalizeURL()
  // checks that pageDirectory is valid directory by initalizing
  if (!pagedir_init(argv[2])) {
    fprintf(stderr, "pageDirectory is not writeable\n");
    exit(1);
  }
  // checks maxDepth is in range [0-10]
  if (atoi(argv[3]) < 0 || atoi(argv[3]) > 10) {
    fprintf(stderr, "maxDepth must be in range [0,10]\n");
    exit(1);
  }
}

/**************** crawl ****************/
/* Loops over pages to explore until list is exhausted
 * 
 * Caller provides:
 *   seedURL as a char*, pageDirectory as a valid directory, 
 *   and an integer for maxDepth
 * We do:
 *   create a hashtable for pages seen, a bag of pages to 
 *   crawl. we add the seedURL to the pag and hashtable then 
 *   cycle through the bag fetching webpages, saving them to 
 *   pageDirectory with valid id, and scanning if they are 
 *   less then maxDepth. then we delete all the memory 
 *   allocated
 */
static void 
crawl(char* seedURL, char* pageDirectory, const int maxDepth)
{
  // initalize type structures
  hashtable_t* pagesSeen = hashtable_new(200); // 200 slots as specified
  bag_t* pagesToCrawl = bag_new();
  webpage_t* page = webpage_new(seedURL, 0, NULL);
  // insert seedURL into hashtable and bag
  hashtable_insert(pagesSeen, seedURL, "");
  bag_insert(pagesToCrawl, page);

  int id = 1; // firts file id
  // cycle through bag
  webpage_t* curr;
  while ((curr = bag_extract(pagesToCrawl)) != NULL) {
    // fetches webpage and saves it to pageDirectory with id
    if (webpage_fetch(curr)) {
      logr("Fetched", webpage_getDepth(curr), webpage_getURL(curr));
      pagedir_save(curr, pageDirectory, id);
      id++;
      // scans webpage if not at maxDepth
      if (webpage_getDepth(curr) < maxDepth) {
        logr("Scanning", webpage_getDepth(curr), webpage_getURL(curr));
        pageScan(curr, pagesToCrawl, pagesSeen);
      }
    }
    webpage_delete(curr); // frees webpage from while loop
  }
  bag_delete(pagesToCrawl, webpage_delete); // frees bag while deleting webpages
  hashtable_delete(pagesSeen, NULL); // frees hashtable
}

/**************** pageScan ****************/
/* Extracta URLs from webpages and processes each one
 * 
 * Caller provides:
 *   valid webpage to be scaned, valid bag of pages to 
 *   crawl, and valid hashtable with pages already seen
 * We do:
 *   while there is another URL in the page, check if 
 *   its internal, then check if it has already been 
 *   seen. if not seen add to hashtable and bag then 
 *   free all memory
 */
static void 
pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{
  // initalize variables
  int pos = 0;
  char* nextURL;

  // cycles through while another URL in the page
  while ((nextURL = webpage_getNextURL(page, &pos)) != NULL) {
    logr("Found", webpage_getDepth(page), nextURL);
    if (isInternalURL(nextURL)) { // checks webpage is internal
      if (hashtable_insert(pagesSeen, nextURL, "")) { // checks to see if webpage has been seen
        // adds new webpage to bag
        webpage_t* seen = webpage_new(nextURL, webpage_getDepth(page) + 1, NULL);
        bag_insert(pagesToCrawl, seen);
        logr("Added", webpage_getDepth(page), nextURL);
      } else {
        logr("IgnDupl", webpage_getDepth(page), nextURL);
        // duplicate webpage so freed
        free(nextURL);
      }
    } else {
      logr("IgnExtrn", webpage_getDepth(page), nextURL);
      // external webpage so freed
      free(nextURL);
    }
  }
}

// log one word (1-9 chars) about a given url                                   
static void 
logr(const char *word, const int depth, const char *url)
{
#ifdef APPTEST
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
#else // APPTEST
  ;
#endif // APPTEST
}
