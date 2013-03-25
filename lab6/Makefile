# $Id: Makefile,v 1.7 2012-11-08 18:35:57-08 - - $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = nsort.c lsort.c
SOURCES  = ${CSOURCES} Makefile
EXECBINS = nsort   lsort
LISTING  = ../lab6c.nsort-lsort.ps
SUBMIT   = submit cmps012b-wm.f12 lab6

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

ci :
	cid + ${SOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

