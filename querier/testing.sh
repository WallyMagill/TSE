#!/bin/bash
#
# testing.sh - testing script for querier module
#
# To Use call in terminal:
#   make test &> testing.out
#
# Goes through a lot of test for inputs in
# querier.
#
# Wally Magill, Febuary 2023

# Define myvalgrind for test
myvalgrind='valgrind --leak-check=full --show-leak-kinds=all'

# Test 1: no arguments
./querier

# Test 2: one arguments
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2

# Test 3: too many arguments
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2 ~/cs50-dev/shared/tse/output/data/toscrape-index-2 tooManyArgs

# Test 4: invalid pageDirectory (non-existant path)
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-100 ~/cs50-dev/shared/tse/output/data/toscrape-index-2

# Test 5: invalid pageDirectory (not a crawler directory)
./querier ~/cs50-dev/shared/tse/output/data ~/cs50-dev/shared/tse/output/data/toscrape-index-2

# Test 6: invalid indexFilename
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2 ~/cs50-dev/shared/tse/output/data/toscrape-index-100

# Test 7: non-valid-querier (runs querier on invalid inputs)
# NOTE: formatting looks weird through this but when it is run in terminal it has correct formatting
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2 ~/cs50-dev/shared/tse/output/data/toscrape-index-2 < non-valid-querier.txt 

# Test 8: valid-querier (runs querier on valid inputs)
./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2 ~/cs50-dev/shared/tse/output/data/toscrape-index-2 < valid-querier.txt 

# Test 9: myvalgrind on valid-querier (runs querier on valid inputs)
$myvalgrind ./querier ~/cs50-dev/shared/tse/output/data/toscrape-depth-2 ~/cs50-dev/shared/tse/output/data/toscrape-index-2 < valid-querier.txt