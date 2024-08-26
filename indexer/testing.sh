#!/bin/bash
#
# testing.sh - testing script for index module
#
# To Use call in terminal:
#   make test &> testing.out
#
# Goes through a lot of test for indexer and
# indextest. indexer is ran then indextest. we
# also use the function indexcmp provided by
# the lab to compare output and results.
#
# Wally Magill, Febuary 2023

# Creates nessesary directorie
mkdir index-outputs

# Define myvalgrind for test
myvalgrind='valgrind --leak-check=full --show-leak-kinds=all'

# Test 1: no arguments
./indexer

# Test 2: one arguments
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0

# Test 3: too many arguments
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0 index-output/letters-index-0.out tooManyArgs

# Test 4: invalid pageDirectory (non-existant path)
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-100 index-outputs/letters-index-0.out

# Test 5: invalid pageDirectory (not a crawler directory)
./indexer ~/cs50-dev/shared/tse/output/data index-outputs/letters-index-0.out

# Test 6: invalid indexFilename (non-existant path)
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0 not-index-outputs/letters-index-0.out

# Test 7: invalid indexFilename (read-only directory)
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0 ~/cs50-dev/shared/tse/output/data/letters-depth-0

# Test 8: invalid indexFilename (existing, read-only file)
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0 ~/cs50-dev/shared/tse/output/data/letters-depth-0/1


# Test 9: letters-0

# Test 9a: indexer on letters-0
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-0 index-outputs/letters-index-0.out

# Test 9b: comparing output for indexer letters-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/letters-index-0 index-outputs/letters-index-0.out

# Test 9c: indextest on indexer for letters-0
./indextest index-outputs/letters-index-0.out index-outputs/letters-index-0.test

# Test 9d: comparing output for indextest letters-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/letters-index-0 index-outputs/letters-index-0.test


# Test 10: letters-6

# Test 10a: indexer on letters-6
./indexer ~/cs50-dev/shared/tse/output/data/letters-depth-6 index-outputs/letters-index-6.out

# Test 10b: comparing output for indexer letters-6
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/letters-index-6 index-outputs/letters-index-6.out

# Test 10c: indextest on indexer for letters-6
./indextest index-outputs/letters-index-6.out index-outputs/letters-index-6.test

# Test 10d: comparing output for indextest letters-6
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/letters-index-6 index-outputs/letters-index-6.test


# Test 11: toscrape-0

# Test 11a: indexer on toscrape-0
./indexer ~/cs50-dev/shared/tse/output/data/toscrape-depth-0 index-outputs/toscrape-index-0.out

# Test 11b: comparing output for indexer toscrape-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-0 index-outputs/toscrape-index-0.out

# Test 11c: indextest on indexer for toscrape-0
./indextest index-outputs/toscrape-index-0.out index-outputs/toscrape-index-0.test

# Test 11d: comparing output for indextest toscrape-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-0 index-outputs/toscrape-index-0.test


# Test 12: toscrape-1

# Test 12a: indexer on toscrape-1
./indexer ~/cs50-dev/shared/tse/output/data/toscrape-depth-1 index-outputs/toscrape-index-1.out

# Test 12b: comparing output for indexer toscrape-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-1 index-outputs/toscrape-index-1.out

# Test 12c: indextest on indexer for toscrape-1
./indextest index-outputs/toscrape-index-1.out index-outputs/toscrape-index-1.test

# Test 12d: comparing output for indextest toscrape-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-1 index-outputs/toscrape-index-1.test


# Test 13: wikipedia-0

# Test 13a: indexer on wikipedia-0
./indexer ~/cs50-dev/shared/tse/output/data/wikipedia-depth-0 index-outputs/wikipedia-index-0.out

# Test 13b: comparing output for indexer wikipedia-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/wikipedia-index-0 index-outputs/wikipedia-index-0.out

# Test 13c: indextest on indexer for wikipedia-0
./indextest index-outputs/wikipedia-index-0.out index-outputs/wikipedia-index-0.test

# Test 13d: comparing output for indextest wikipedia-0
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/wikipedia-index-0 index-outputs/wikipedia-index-0.test


# Test 14: wikipedia-1

# Test 14a: indexer on wikipedia-1
./indexer ~/cs50-dev/shared/tse/output/data/wikipedia-depth-1 index-outputs/wikipedia-index-1.out

# Test 14b: comparing output for indexer wikipedia-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/wikipedia-index-1 index-outputs/wikipedia-index-1.out

# Test 14c: indextest on indexer for wikipedia-1
./indextest index-outputs/wikipedia-index-1.out index-outputs/wikipedia-index-1.test

# Test 14d: comparing output for indextest wikipedia-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/wikipedia-index-1 index-outputs/wikipedia-index-1.test


# Test 15: myvalgrind

# Test 15a: myvalgrind indexer on toscrape-1
$myvalgrind ./indexer ~/cs50-dev/shared/tse/output/data/toscrape-depth-1 index-outputs/toscrape-index-1.out

# Test 15b: comparing output for indexer toscrape-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-1 index-outputs/toscrape-index-1.out

# Test 15c: myvalgrind indextest on indexer for toscrape-1
$myvalgrind ./indextest index-outputs/toscrape-index-1.out index-outputs/toscrape-index-1.test

# Test 15d: comparing output for indextest toscrape-1
~/cs50-dev/shared/tse/indexcmp ~/cs50-dev/shared/tse/output/data/toscrape-index-1 index-outputs/toscrape-index-1.test