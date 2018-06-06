#
# Makefile
# weihao, 2018-06-04 15:09
#

all:
	flex spl.l
	bison -d spl.y
	clang++ -g -std=c++11 lex.yy.c spl.tab.c cst.cpp translator.cpp tree.cpp common.cpp -lfl

clean:
	rm lex.yy.c spl.tab.* *.json a.out

# vim:ft=make

