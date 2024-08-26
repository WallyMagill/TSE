/*
 * index.h - header file for index.c
 *
 * A *index* is a hashtable that has words as 
 * keys and contains counters as items. In the 
 * counter is the file ID and number of 
 * occurences.
 * 
 * Wally Magill, Febuary 2023
 */

#ifndef __INDEX_H
#define __INDEX_H

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

/**************** index_new ****************/
/* Create a new (empty) index.
 *
 * Caller provides:
 *   number of slots to be used for the index (must be > 0).
 * We return:
 *   pointer to the new index; return NULL if error.
 * We guarantee:
 *   index is initialized empty.
 * Caller is responsible for:
 *   later calling index_delete.
 */
index_t* index_new(int slots);

/**************** index_find ****************/
/* Return the item associated with the given key.
 *
 * Caller provides:
 *   valid pointer to index, valid string for key.
 * We return:
 *   pointer to the item corresponding to the given key, if found;
 *   NULL if hashtable is NULL, key is NULL, or key is not found.
 * Notes:
 *   the index is unchanged by this operation.
 */
void* index_find(index_t* index, char* key);

/**************** index_insert ****************/
/* Insert item, identified by key (string), into the given index.
 *
 * Caller provides:
 *   valid pointer to index, valid string for key, valid pointer for item.
 * We return:
 *   false if key exists in index, any parameter is NULL, or error;
 *   true if new item was inserted.
 */
bool index_insert(index_t* index, char* key, void* item);

/**************** index_delete ****************/
/* Delete index, calling a delete function on each item.
 *
 * Caller provides:
 *   valid index pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if index==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the index itself.
 * Notes:
 *   We free the strings that represent key for each item, because 
 *   this module allocated that memory in index_insert.
 */
void index_delete(index_t* index);

/**************** index_save ****************/
/* Saves all items in the index; to a file.
 *
 * Caller provides:
 *   valid pointer to index, 
 *   valid pointer to file
 * We do:
 *   iterate through the index using helper functions to 
 *   print the contants to a file so it can be read later
 * Notes:
 *   the format is specifically made so that it can be read
 *   for later use and consist of each word on its own line
 *   with the counters contents after
 */
void index_save(index_t* index, FILE* fp);

/**************** index_load ****************/
/* Loads all items in file to index.
 *
 * Caller provides:
 *   valid pointer to index, 
 *   valid pointer to file
 * We do:
 *   iterate through the file pulling components and 
 *   constructing the index
 * Notes:
 *   the format is specifically made so that it can be read
 *   and consist of each word on its own line with the 
 *   counters contents after
 */
void index_load(index_t* index, FILE* fp);

#endif // __INDEX_H