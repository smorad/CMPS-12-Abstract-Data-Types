# $Id: Makefile,v 1.1 2012-10-18 13:19:38-07 - - $
#Lauren Crowther lcrowthe
#Steven Morad smorad 
JAVASRC    = keyvalue.java linkedlist.java pair.java messages.java
SOURCES    = ${JAVASRC} Makefile README
ALLSOURCES = ${SOURCES} pkeyvalue.perl
MAINCLASS  = keyvalue
CLASSES    = ${JAVASRC:%.java=%.class}
JARCLASSES = ${CLASSES} linkedlist\$$*.class
JARFILE    = keyvalue
SUBMIT     = submit cmps012b-wm.f12 asg2

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	cid + $<
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${ALLSOURCES}
	cid + ${ALLSOURCES}

lis : ${ALLSOURCES}
	mkpspdf ../asg2j-keyvalue.code.ps ${ALLSOURCES}

submit :
	${SUBMIT} ${SOURCES}

again : ${ALLSOURCES}
	make --no-print-directory spotless ci all lis

