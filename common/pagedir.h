/*
 * pagedir.h - header file for pagedir.c
 *
 * The file pagedir.c helps crawler.c by intializing the 
 * pageDirectory with a .crawler file and saves webpages 
 * into the directory by a docID
 * 
 * Wally Magill, Febuary 2023
 */

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../libcs50/mem.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

/**************** pagedir_init ****************/
/* Construct the pathename for .crawler file in directory.
 * 
 * Caller provides:
 *   valid directory name
 * We return:
 *   true if .crawler was able to be constructerd in the file
 *   with out any erros, return false otherwise.
 * We guarantee:
 *   the directory has .crawler and files can be writen into it
 * We do:
 *   create a .crawler function by opening it to write inside 
 *   the directory and then close the file returning true. we 
 *   return false if the file is not created
 */
bool pagedir_init(const char* pageDirectory);

/**************** pagedir_save ****************/
/* Saves the webpage to a file in pageDirectory
 * 
 * Caller provides:
 *   valid webpage_t page
 *   valid directory full of pages
 *   correct ID for the given file
 * We do:
 *   create a file in pageDirectory with the given ID. then 
 *   we write the URL on first line, depth on second line, 
 *   and the HTML code starting on the third line
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/**************** pagedir_validate ****************/
/* Validates that the given pageDirectroy is not NULL. We
 * also ensure that it is a crawler directory and has readable
 * files.
 *
 * Caller provides:
 *   valid directory name
 * We return:
 *   true if the pageDirectory is a valid directory created by
 *   crawler with readable files inside
 * We guarantee:
 *   the directory has .crawler and files can be read
 * We do:
 *   check if the directory is NULL. then check for a readable
 *   ".crawler" file and a readable "1" file.
 */
bool pagedir_validate(char* pageDirectory);

/**************** pagedir_load ****************/
/* Loads the page from a valid file written in Crawler format 
 *
 * Caller provides:
 *   valid file pointer
 * We return:
 *   a webpage with valid -> (URL, Depth, and HTML)
 * We do:
 *   create char* for URL, Depth, and HTML then declares
 *   variables by reading the file. then the webpage is 
 *   constructed and allocated memory is freed
 * 
 */
webpage_t* pagedir_load(FILE* fp);

#endif // __PAGEDIR_H