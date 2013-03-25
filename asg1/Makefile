# $Id: Makefile,v 1.1 2012-10-01 19:42:51-07 - - $

JAVASRC    = jgrep.java options.java messages.java
SOURCES    = README Makefile ${JAVASRC}
MAINCLASS  = jgrep
CLASSES    = jgrep.class options.class messages.class
JARFILE    = jgrep
JARCLASSES = ${CLASSES}
SUBMITDIR  = cmps012b-wm.f12 asg1

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
	) >test.output
	cat -nv test.output

submit: check ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}

again:
	gmake --no-print-directory spotless ci all test check

