# README.md
## Indexer Module
### Wally Magill, Febuary 2023

Inside this module is querier.c

### Indexer.c

Querier is created off of the requirements from LAB 6. I created a design and implementation file on how I planned to construct the programs. This is part of the tiny serach engine project and is the querier module that is able to search an index based on inputs from user, displaying the results ranked in desending order. We assume pageDirectory has files named 1, 2, 3, ..., without gaps and the content of files in pageDirectory follow the format as defined in the specs. We also assume that indexFilename is properly formated accourding to the output of the index module. For information on implementation look at querier.c. To build the querier use the command `$ make`. To test querier run `$ make test &> testing.out` which will run a bash script writing to testing.out. To clean the subdirectory, `$ make clean`.

### Notes:

Both late days were used on this LAB.

I did use the function strtok although it was mentioned that it may cause issues. This is because strtok can cause issues as it is not a terribly safe function. One alternative posibility is strtok_r which could be considered safer.

I also have not had the best git flow practices. This is mostly because I did not want to mess up any of my previous submits. This is why I did not activly commit my files.
