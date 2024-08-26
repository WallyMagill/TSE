# CS50 TSE Indexer
## Implementation Spec
### Wally Magill, Febuary 2023
Indexer is a function that reads files from a pageDirectory created by crawler, creates webpages, and builds an index so the number of instances of each word in each document is tracked. Then the index is printed to a file.

## Data Structure
We will create the data structure index_t* for use in this module. It is a hashtable that stores words and counters. Inside the counters is docIDs and counts of word occurences. 

The data structure is specified in index.c (index.h has information for how the functions inside index.c are implemented.

## Control Flow
Indexer is implemented in indexer.c which has four functions.

### main
The main function calls validateArgs to chek arguments. If this succsseds then it opens a file, calls indexBuild, then index_save to write the index into a given file, finally the index is deleted and file is closed. If everything is run successfully we return 0.

### validateArgs
This confirms that the arguments provided are valid.

It first ensures that there are two arguments provided. Then it checks there is a .crawler file in the given pageDirectory. Finally it checks that there is a readable '1' file in pageDirectory.

If there are any errors we print to stderr and exit non zero.

### indexBuild
This builds an index from a given pageDirectory.

Pseudocode:
```
initalize all variables and structures for index, wepage, and file
create int id and set to 1
create the path name for the '1' file in pageDirectory
cycle through filename increasing by 1 each time
	load the webpage from file
	call indexPage
	close file and delete webpage
	increase id and change path name
free file name
return index
```

### indexPage
This scans the webpage and puts information into index.

Pseudocode:
```
initalizes counters
creates both word char* and pos int
cycle through words in webpage
	checks length of word is over 2
		normalize word
		checks for counters
		if does not exist
			create new counters
			add id to counters
			insert counters into index
		else
			incriment counters
	frees word
```

## Other Modules
### pagedir
#### pagedir_validate
We check if there is a '.crawler' and '1' file in the given page directory. If the files can be read then the directory is a readable crawler directory and can be used for indexer.

#### pagedir_load
Given a pageDirectory file it creates a webpage. This is done by reading lines of the file for the url, depth, and html.

### word
#### normalizeWord
We loop through the entire word making each character lower case. Then returns the new lower case word.

### index
We create the index_t* data structure and create functions to manipulate the data with in. Most of the functions are wrapper functions for hashtable. For more information look at the file index.h.

### libsc50
We use data structures and modules contained within libcs50 given to us.

## Function Prototypes
Descriptions of each function and how they work are found within each file.

### indexer
```C
main(int argc, char* argv[]);
static void validateArgs(int argc, char* argv[]);
static index_t* indexBuild(char* pageDirectory);
static void indexPage(index_t* index, webpage_t* webpage, int id);
```

### pagedir
```C
bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(char* pageDirectory);
webpage_t* pagedir_load(FILE* fp);
```

### word
```C
void normalizeWord(char* word);
```

### index
```C
typedef hashtable_t index_t;
index_t* index_new(int slots);
void* index_find(index_t* index, char* key);
bool index_insert(index_t* index, char* key, void* item);
void index_delete(index_t* index);
void index_save(index_t* index, FILE* fp);
void index_load(index_t* index, FILE* fp);
```

## Error Handling and Recovery
There is a lot less error handling as the inputs come from the crawler function so we know how the files will look allowing for easier success. The command-line arguments are checked to make sure that the functions are able to run. If there is an error there then an error message is printed to stderr and exits non zero.

All code uses defensive-programming with cs50 recomendations.

## Testing
We created a bash script called testing.sh to allow us to check if indexer.c works as intended. It does this by using the compare function provided to compare the output to the correct output already provided. 

We also test indextest to make sure the index can be loaded and saved successfully.

We also run myvalgrind to check for zero memory leaks in the program.

The test we preformed were on letters-depth-0, letters-depth-6, toscrape-depth-0, toscrape-depth-1, wikipidia-depth-0 and wikipidia-depth-1.
