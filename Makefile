#
# Makefile
# weihao, 2018-06-04 15:09
#

all:
	flex spl.l
	bison -d spl.y
	clang++ -g -std=c++11 `llvm-config --cxxflags --ldflags --system-libs --libs core` lex.yy.c spl.tab.c cst.cpp translator.cpp tree.cpp common.cpp codegen.cpp -lfl -o tester

clean:
	rm lex.yy.c spl.tab.*

# vim:ft=make

