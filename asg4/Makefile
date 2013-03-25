# $Id: Makefile,v 1.1 2012-11-19 19:57:43-08 - - $
MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
SUBMAKE   = ${MAKE} --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MAKEDEPS  = cc -MM

CHEADER   = list.h debugf.h
CSOURCE   = edfile.c ${CHEADER:.h=.c}
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = edfile
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTING   = asg4c-edfile.code.ps
SUBMIT    = submit cmps012b-wm.f12 asg4
all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

ci : ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core

spotless : clean
	- rm ${EXECBIN}

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MAKEDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${SUBMAKE} deps

again :
	${MAKE} --no-print-directory spotless deps ci all lis

submit :
	${SUBMIT} ${SOURCES}

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

