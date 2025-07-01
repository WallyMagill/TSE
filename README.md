# Tiny Search Engine

The **Tiny Search Engine (TSE)** is a modular C-based backend system that indexes webpages and processes search queries to return ranked document results. It supports logical operators (`AND`, `OR`) and provides robust, memory-safe performance with defensive coding practices and rigorous testing.

## Features

- Parses and validates user queries with proper logical structure
- Supports operator precedence (`AND` before `OR`)
- Performs intersection and union of indexed document sets
- Ranks and sorts search results based on document relevance
- Defensive programming style: handles `NULL` pointers and improper inputs gracefully
- Fully memory-leak-free with Valgrind verification

## How It Works

1. **Index Loading**: Loads an inverted index from disk (created using a separate crawler and indexer).
2. **Query Processing**:
   - Validates query format and normalizes input
   - Tokenizes the query and applies precedence rules
   - Processes each query using custom hashtable and counter structures
3. **Ranking**:
   - For `AND`, computes the minimum score intersection
   - For `OR`, computes the sum score union
   - Results are sorted and displayed by relevance
4. **Testing**: Includes comprehensive bash test scripts and regression testing tools

## Technologies

- **Language**: C
- **Build Tools**: Make, Bash
- **Data Structures**: Custom Hash Tables, Counters
- **Memory Management**: Manual (verified with Valgrind)
- **Environment**: Unix-based terminal

## Example Output

```bash
Query? climate AND change
# Matching 3 documents
1. ./pages/page17.html (score: 8)
2. ./pages/page3.html (score: 6)
3. ./pages/page9.html (score: 4)
