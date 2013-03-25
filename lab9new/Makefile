# $Id: Makefile,v 1.1 2012/12/01 19:05:59 smorad Exp $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = numsort.c linesort.c inssort.c
SOURCES  = ${CSOURCES} Makefile PARTNER README  inssort.h
EXECBINS = numsort   linesort
LISTING  = ../lab6c.nsort-lsort.ps
SUBMIT   = submit cmps012b-wm.f12 lab9

all : numsort linesort

numsort: numsort.o inssort.o
	${GCC} numsort.o inssort.o -o numsort

linesort: linesort.o inssort.o
	${GCC} linesort.o inssort.o -o linesort

%.o : %.c
	- checksource $<
	${GCC} $< -c $<


ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	- checksource ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

