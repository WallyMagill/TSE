# README.md
## Indexer Module
### Wally Magill, Febuary 2023

Inside this module is indexer.c and indextest.c  

### Indexer.c

Indexer is created off of the requirements and design from LAB 5. I created an implementation file on how I planned to construct the programs. This is part of the tiny serach engine project and is the indexer module that is able to construct an index based off of the outputs from crawler. We assume pageDirectory has files named 1, 2, 3, ..., without gaps and the content of files in pageDirectory follow the format as defined in the specs; thus the code (to read the files) need not have extensive error checking. For information on implementation look at indexer.c. To build the crawler use the command `$ make all`. To test crawler run `$ make test &> testing.out` which will run a bash script writing to testing.out. To clean the subdirectory, `$ make clean`.

### Indextest.c

Indextest is created to transcribe the index from one file to another by taking the output of indexer. We assume the content of the index file follows the format specified; thus the code (to recreate an index structure by reading a file) need not have extensive error checking.For information on implementation look at indextest.c. To build the crawler use the command `$ make all`. To test crawler run `$ make test &> testing.out` which will run a bash script writing to testing.out. To clean the subdirectory, `$ make clean`.

