# README.md
## Common Module
### Wally Magill, Febuary 2023

Inside this module is the file pagedir.c, pagedir.h, word.c, word.h, index.c, and index.h

### pagedir

These files help the crawler and indexer module by handling page directory and webpages. The file is implemented per the specs of implementation in the LAB 4/5 assignment. There is also no assumptions that are made. For information on implementation look at pagedir.h. To build the library common.a use the command `$ make`. To clean the subdirectory, `$ make clean`.

### word

These files help the indexer module by noramlizing words. The file is implemented per the design specs in the LAB 5 assignment and the implementation file. There is also no assumptions that are made. For information on implementation look at pagedir.h. To build the library common.a use the command `$ make`. To clean the subdirectory, `$ make clean`.

### index

These files help the indexer module by creating index type structure (moslty wrapping hashtable). The file is implemented per the design specs in the LAB 5 assignment and the implementation file. There is also no assumptions that are made. For information on implementation look at pagedir.h. To build the library common.a use the command `$ make`. To clean the subdirectory, `$ make clean`.
