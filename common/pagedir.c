/*
 * pagedir.c - see pagedir.h for more information
 *
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../libcs50/mem.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

/**************** pagedir_init ****************/
/* see pagedir.h for description */
bool 
pagedir_init(const char* pageDirectory)
{
  FILE* fp;

  char* fileName = (char*)mem_malloc(strlen(pageDirectory) + strlen("/.crawler") + 1); // need extra space for '\0'
  sprintf(fileName, "%s/.crawler", pageDirectory); // writes file name to string buffer
  // Checks if file is writeable
  if ((fp = fopen(fileName, "w")) == NULL) {
    mem_free(fileName);
    return false;
  }
  fclose(fp);
  mem_free(fileName);
  return true;
}

/**************** pagedir_save ****************/
/* see pagedir.h for description */
void 
pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
  FILE* fp;
  int docIDmemory = log10(docID) + 1;

  char* fileName = (char*)mem_malloc(strlen(pageDirectory) + docIDmemory + 2); // need extra space for '/' and '\0'
  sprintf(fileName, "%s/%d", pageDirectory, docID); // writes file name to string buffer
  fp = fopen(fileName, "w"); // opens new file to write
  fprintf(fp, "%s\n%d\n%s\n", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page)); // prints all info to file
  fclose(fp);
  mem_free(fileName);
}

/**************** pagedir_validate ****************/
/* see pagedir.h for description */
bool
pagedir_validate(char* pageDirectory)
{
  // checks if NULL
  if (pageDirectory == NULL) {
    fprintf(stderr, "Invalid pageDirectory. The pageDirectory is NULL.\n");
    return false;
  }
  // check for readable .crawler
  FILE* fp;
  char* fileName = (char*)mem_malloc(strlen(pageDirectory) + strlen("/.crawler") + 1);
  sprintf(fileName, "%s/.crawler", pageDirectory);
  if ((fp = fopen(fileName, "r")) == NULL) {
    fprintf(stderr, "Invalid pageDirectory. The pageDirectory does not have a readable '.crawler' file.\n");
    mem_free(fileName);
    return false;
  }
  fclose(fp);
  // check for readable '1'
  sprintf(fileName, "%s/1", pageDirectory);
  if ((fp = fopen(fileName, "r")) == NULL) {
    fprintf(stderr, "Invalid pageDirectory. The pageDirectory does not have a readable '1' file.\n");
    mem_free(fileName);
    return false;
  }
  fclose(fp);
  mem_free(fileName);
  return true;
}

/**************** pagedir_load ****************/
/* see pagedir.h for description */
webpage_t*
pagedir_load(FILE* fp)
{
  // initalize webpage
  webpage_t* webpage;
  // initalize variables
  char* url;
  char* depthStr;
  char* html;
  int depth; // need to covert to int
  // reads line for variable and cast if nessesary
  url = file_readLine(fp);
  depthStr = file_readLine(fp);
  depth = atoi(depthStr);
  html = file_readFile(fp);// reads rest of file
  // creates webpage
  webpage = webpage_new(url, depth, html);
  // free memeory not needed
  free(depthStr);
  return webpage;
}