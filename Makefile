#
# Makefile
# weihao, 2018-06-04 15:09
#

all:
	flex spl.l
	bison -d spl.y
	g++ lex.yy.c spl.tab.c cst.cpp translator.cpp tree.cpp -lfl

clean:
	rm lex.yy.c spl.tab.*

# vim:ft=make

