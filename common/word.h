/*
 * word.h - header file for word.c
 *
 * The file word.c helps indexer.c by normalizing
 * words (turning all letters lower case).
 * 
 * Wally Magill, Febuary 2023
 */

#ifndef __WORD_H
#define __WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************** normalizeWord ****************/
/* Turns all letters to lower case in a word
 * 
 * Caller provides:
 *   valid char* word
 * We Garentee:
 *   word is not NULL
 * We do:
 *   check if word is NULL. then cycke through
 *   each letter and turn lower case
 */
void normalizeWord(char* word);

#endif // __WORD_H