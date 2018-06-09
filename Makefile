NAME = spl

LLVM_CONFIG = /usr/local/bin/llvm-config

NO_WARNING =  -Wno-return-type \
	-Wno-c++11-compat-deprecated-writable-strings \
	-Wno-deprecated-register \
	-Wno-switch \

CXXFLAGS = `$(LLVM_CONFIG) --cppflags` -std=c++11 $(NO_WARNING)
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LIBS = `$(LLVM_CONFIG) --libs --system-libs`

all:
	flex -o tokenizer.cpp ${NAME}.l
	bison -d -o parser.cpp ${NAME}.y
	clang++ -g ${CXXFLAGS} *.cpp $(LIBS) $(LDFLAG) -lfl -o tester

# make debug - check the bison output report
debug:
	bison -d -o parser.cpp ${NAME}.y -v

clean:
	@rm -f parser.output *.o parser.cpp parser.hpp tokenizer.cpp tester

