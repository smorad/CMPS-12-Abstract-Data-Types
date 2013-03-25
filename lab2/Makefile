# $Id: Makefile,v 1.1 2012-10-01 19:42:51-07 - - $

JAVASRC    = exit255.java
SOURCES    = README Survey Makefile ${JAVASRC}
MAINCLASS  = exit255
CLASSES    = exit255.class
JARFILE    = exit255
JARCLASSES = ${CLASSES}
SUBMITDIR  = cmps012b-wm.f12 lab2

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class: %.java
	cid + $<
	javac $<

clean:
	- rm ${CLASSES} test.output

spotless: clean
	- rm ${JARFILE}
	- ls -ago

ci: ${SOURCES}
	cid + ${SOURCES}

check: ${SOURCES}
	- checksource ${SOURCES}

test: ${JARFILE}
	( echo "%%%%%%%% ${JARFILE}" \
	; ${JARFILE} 2>&1 \
	; echo "%%%%%%%% Exit status = $$?" \
	; echo "%%%%%%%% uname -a" ; uname -a \
	) >255.output
	cat -nv 255.output

submit: check ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again:
	gmake --no-print-directory spotless ci all test check

