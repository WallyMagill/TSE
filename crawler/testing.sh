#!/bin/bash
#
# testing.sh - testing script for crawler module
#
# To Use call in terminal:
#   make test &> testing.out
#
# Goes through a lot of test for crawler. Some 
# test may be commented out just because of time 
# concerns. Goal is to test limits of the program.
#
# Wally Magill, Febuary 2023

# Creates nessesary directories
mkdir data
mkdir data/letters-0
mkdir data/letters-1
mkdir data/letters-2
mkdir data/letters-10
mkdir data/toscrape-0
mkdir data/toscrape-1
mkdir data/toscrape-2
mkdir data/toscrape-3
mkdir data/wikipedia-0
mkdir data/wikipedia-1
mkdir data/wikipedia-2

# Define myvalgrind for test
myvalgrind='valgrind --leak-check=full --show-leak-kinds=all'

# This test format was part of the INTEGRATION 
# file inside crawler. The commented out test were 
# recommended in the README file of crawler due to 
# the excessive run time, saying that these test 
# are sufficent.

# Test 1: no arguments
./crawler

# Test 2: too many arguments
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-0 0 testArgument

# Test 3: external URL
./crawler https://home.dartmouth.edu/ data/letters-0 0

# Test 4: non-existent directory
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/testDirectory 0

# Test 5: maxDepth too low
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-0 -2

# Test 6: maxDepth too high
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-0 12

# Test 7: myvalgrind on torscrape depth 1
$myvalgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape-1 1

# Test 8: letters depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-0 0

# Test 9: letters depth 1
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-1 1

# Test 10: letters depth 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-2 2

# Test 11: letters depth 10
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html data/letters-10 10

# Test 12: toscrape depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape-0 0

# Test 13: toscrape depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape-1 1

# Test 14: toscrape depth 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape-2 2

# Test 15: toscrape depth 3
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ data/toscrape-3 3

# Test 16: wikipedia depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ data/wikipedia-0 0

# Test 17: wikipedia depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ data/wikipedia-1 1

# Test 18: wikipedia depth 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ data/wikipedia-2 2
