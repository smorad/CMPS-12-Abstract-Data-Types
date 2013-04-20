CMPS-12-Abstract-Data-Types
===========================

Code is written in either C or Java

Assignments
==========================

Asg1: A version of of the Unix grep command written in Java. Demonstrates knowledge in IO on the Unix OS.
Syntax: jgrep -ilnv 'filename'

Asg2: Linked list implementation using key-value pairs. Linear time searches with a linked list. 

Asg3: Ignore, correct version is Asg3New

Asg3New: Takes input and puts input in a linked list, then places linked lists into a binary tree. Counts the number of times a word appears in a file(s).

Asg4: A simple text editor using doubly linked lists. Commands are as follows:
    # and whitespace are ignored
    * : prints document to stdout
    . : views text on current line
    $ : go to last line
    0 : go to first line
    < : move one line up
    > : move one line forward
    @ : debug dump
    a : inserts text after 'a' into document after current line
    d : deletes current line
    i : inserts text after 'i' before current line
    r : opens a file to edit
    w : saves file to char* following 'w'

Asg5: A spellchecker. Loads specified dictionary into a hashset and then spell checks a file or from stdin. If no dictionary is specified, default Unix dictionary is used. This program uses the yy_flex library.

Labs
============================
Lab1: Prints out some Unix system variables
Lab2: Returns specified exit status
Lab3: Polish notation calculator. Pushes doubles and operators onto a stack and pops them off to calculate. Done in C and Java
Lab4: Code is on another machine. Will update this in time.
Lab5: Many small programs demonstrating memory management and allocation
Lab6: two sorting algorithms, one for strings and one for integers
Lab7: Puts files in queues, demonstrating memory management
Lab8: Use of Unix symlink to read file attributes. Also extended use of <time.h> to convert timestamp attributes to readable formats
Lab9/Lab9new: Use of void* and pointer arithmetic to sort arrays of many types. Basically an attempt at generics in C.
