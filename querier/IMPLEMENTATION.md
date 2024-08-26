# CS50 TSE Querier
## Implementation Spec
### Wally Magill, Febuary 2023

This file was written using the IMPLEMENTATION.md from crawler.

## Data structures

A few different data structures are used in this module:
`index` created from indexFilename
`counters` store docIDs and their counts for documents matching query
`counters_pair` holds two counters so that it can be used in iterating
`score` holds both a docID and score for matching documents

## Control Flow

The Querier is implemented in one file querier.c, with four main functions with many helper functions throughout.

### main

The `main` function simply calls `validateArgs`. It then creates the index from the file. Then it runs `startQuery` which inturn calls `runQuery`. If it is successful then returns zero.

### validateArgs

This validates the command line arguments for querier.

### startQuery

Pseudocode:

    promps query
    cycles through query inputs
        checks for non alpha characters
            create array or normalized words
            calls runQuery
            resets prompt
        error for non alpha character
            resets prompt

### runQuery

Pseudocode:

    validates query
        prints clean query
        creates counter results
        finds number of matches
            error for zero matches
        prints header
        creates array of scores
        sorts array of scores
        prints sorted array
        
## Function prototypes

There are many little functions in querier.

All functions are as follows:

```c
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
```

There is more information on each function within querier.c.

These functions are also used in querier.

### Index:

```c
index_t* index_new(int slots);
void index_load(index_t* index, FILE* fp);
void index_delete(index_t* index);
void* index_find(index_t* index, char* key);
```

### pageDir:

```c
bool pagedir_validate(char* pageDirectory);
```

### Word:

```c
void normalizeWord(char* word);
```

### Counters:

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_iterate(counters_t* ctrs, void* arg, 
                      void (*itemfunc)(void* arg, 
                                       const int key, const int count));
void counters_delete(counters_t* ctrs);
```

## Error handling

All the command-line parameters are rigorously checked before any data structures are allocated or work begins; problems result in a message printed to stderr and a non-zero exit status.

All code uses defensive-programming tactics to catch and exit (using variants of the mem_assert functions), e.g., if a function receives bad parameters.

That said, errors with query are all handled seperatly as an error statment is printed to stderr in most cases. These do not exit the function as it is instead just reset and the user is reprompted.

## Testing Plan

As described in DEISGN.md a bash script is used for integration testing. This will test all cases as described and will print to a testing.out file. Further information can be found in the DEISGN.md file.