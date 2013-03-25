#id: mk,v 1.4 2012-10-25 18:13:13-07 - - $
#
# This script takes the names of C source files and compiles them
# into executable images. Each source must be a complete program.
#
for CSOURCE in $*
do
cid + $CSOURCE
checksource $CSOURCE
EXECBIN=‘echo $CSOURCE | sed ’s/\.c$//’‘
gcc -g -O0 -Wall -Wextra -std=gnu99 $CSOURCE -o $EXECBIN -lm
done
