# Tiny Search Engine

Tiny Search Engine is a lightweight command-line search backend written in C. It indexes webpages and processes textual queries to return ranked document results. The codebase is modular and memory safe—Valgrind shows no leaks.

## Key Features
- Inverted index built with custom hashtables and counter sets
- Query parser supporting `AND` and `OR` with correct precedence
- Scores documents and sorts results by relevance
- Separate crawler, indexer and querier modules
- Defensive coding practices and thorough testing

## How It Works
1. **Index Loading** – the querier reads a prebuilt inverted index from disk.
2. **Query Parsing** – user input is normalized, tokenized and validated; `AND` is processed before `OR`.
3. **Scoring** – documents are intersected or unioned using their scores and then sorted for display.

## Technologies
- **Language**: C
- **Data Structures**: custom hashtables and counters
- **Build Tools**: Make and Bash
- **Memory Safety**: verified with Valgrind

## Build and Run
```bash
# compile everything
make
# build the querier module
make -C querier
# run the search engine
./querier <pageDirectory> <indexFilename>
```

## Example Output
```bash
Query? climate AND change
# Matching 3 documents
1. ./pages/page17.html (score: 8)
2. ./pages/page3.html (score: 6)
3. ./pages/page9.html (score: 4)
```

## Directory Structure
```
TSE/
├── crawler/   # web crawler
├── indexer/   # builds the index
├── querier/   # query engine
├── common/    # shared modules
└── libcs50/   # support library
```

## Testing
Run the query module tests:
```bash
make -C querier test
```
Check memory safety (Valgrind required):
```bash
valgrind ./querier <pageDirectory> <indexFilename>
```
