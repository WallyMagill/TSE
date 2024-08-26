/*
 * indextest.c - a program constructed to test index created
 *
 * This is one part of the TSE project. It is intended to index words 
 * with file ids and counts for times appeared.
 * 
 * Usage: ./indextest oldIndexFilename newIndexFilename
 * Further information on inputs in main.
 * 
 * Wally Magill, Febuary 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/index.h"

/* Initalize all helper functions */
static void validateArgs(int argc, char* argv[]);

/**************** main ****************/
/* Calls all the helper functions and handles arguments
 * 
 * Caller provides:
 *   command line arguments:
 *   oldIndexFilename - a file in which to read the index from
 *   newIndexFilename - a file in which to write the index to
 * We return:
 *   zero if ran successfully
 * We do:
 *   call helper functions
 */
int
main (const int argc, char* argv[])
{
  validateArgs(argc, argv); // checks all arguments are valid
  // initialized variables
  index_t* index = index_new(550);
  FILE* fpOldFileName = fopen(argv[1], "r");
  FILE* fpNewFileName = fopen(argv[2], "w");
  // load index from old file
  index_load(index, fpOldFileName);
  // save index to new file
  index_save(index, fpNewFileName);
  // close and delete
  fclose(fpOldFileName);
  fclose(fpNewFileName);
  index_delete(index);
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
    fprintf(stderr, "Invalid command-line arguments.\nUsage: ./indextest oldIndexFilename newIndexFilename\n");
    exit(1);
  }
  // checks oldIndexFilename is readable
  FILE* fp;
  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Invalid oldIndexFilename. The oldIndexfilename can not be read.\n");
    exit(1);
  }
  fclose(fp);
  // checks newIndexFilename is readable
  if ((fp = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Invalid newIndexFilename. The newIndexfilename can not be written in.\n");
    exit(1);
  }
  fclose(fp);
}