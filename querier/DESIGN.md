# CS50 TSE Querier
## Design Spec
### Wally Magill, Febuary 2023

This file was written using the DESIGN.md from indexer.

Using the REQUIREMENT.md file from the querier module I created a program that uses a crawler pageDirectory and an indexer indexFilename, that accepts user input and searches through the index to create a list of ranked results in accordance with the query.

### User interface

The querier's only interface with the user is on the command-line; it must always have two arguments.

```
./querier pageDirectory indexFilename
```

For example, if `letters` is a pageDirectory in `../data`,

``` bash
$ ./querier ../data/letters ../data/letters.index
```

The querier needs to continue to interact with the user. This is done through stdin. The user is able to provide the function with query's. A query is a sequence of words only containg characters and spaces. The user can change the interactions between the query and user by using the operations "and" and "or". This operators are not able to be the first or last word as well as two operators are not able to be adjacent to one another.

### Inputs and outputs

**Input**: The querier needs to read from a given pageDirectory that has been created by crawler. It also needs an indexFilename which is an index created by indexer. After these inputs quary inputs are able to be entered through stdin explained above.

**Output**: The querier outputs a ranked list of documents with a score, docID, and the url. This is all based on the quary provided.

### Functional decomposition into modules

We anticipate the following modules or functions:

1. *main*, which validates arguments and initializes/starts other modules;
2. *validateArgs*, which checks that the arguments are valid
3. *query*, which calls methods to examine quary, create counter, score results, and print the results.
4. *counterCreation*, creates the counter based off of the query
5. *scoreQuery*, constructs an array of docID's and score's
6. *sortScore*, sorts the array of docID's and score's

And some helper modules that provide data structures:

1. *index*, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
2. *word*, a module providing a function to normalize a word.
3. *counter*, a module that stores a key and a count

### Pseudo code for logic/algorithmic flow

This is pseudocode for the entire module. There will be further break down in IMPLEMENTATION.md

Pseudocode:

      validate arguments
            create index
            load the index
            parse queries
                  validate query for characters
                  normalize query
                  validate query for words
                  print the normalized query
                  create a counter using the index and query
                  build an array of scores and docIDs
                  sort the array of scores and docIDs
                  print the results with score, docID, and url
      exit zero with no errors

### Major data structures

There are a few data structures that are needed. The first is a counters_pair which is a simple data structure holding two differnt counters necessary for iterate. We also use a score structure that holds docIDs and scores. Counters and index data structureas are also used throughout the module.

### Testing plan

We will test through integration testing. This means there is a testing.sh bash script that will be run using the make file that will test various test cases. Then we are able to check the output of the test.

The test cases may be as follows:

Command line test:
 1. no arguments
 2. too many arguments
 3. invalid pageDirectory (non-existant path)
 4. invalid pageDirectory (not a crawler directory)
 5. invalid indexFilename

Non valid query test:
- and
- or
- and earth
- or earth
- planet earth or
- planet earth and
- planet earth and or science
- planet earth and and science
- planet earth or and science
- Warning!
- (The Lunar Chronicles #4.5)

Valid query test (weird spacing in actual testing):
- think
- think        how
- thINk       or    how
- think and       HOW
- think     Or hoW AnD become
- human and ThinK and become
- human OR   think or become
- human and thINk or become
- pages see or america other or club
- pages and see america or other or club

Also run valid query with myvalgrind.