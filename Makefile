# Compiler
CC = g++

# Lib Flags
LF = -c
LIBS_PATH = ./lib/
SRC_PATH = ./src/
H_PATH = ./headers/

# Objects
OBJS = $(LIBS_PATH)BitBoard.o $(LIBS_PATH)GOL.o $(LIBS_PATH)GOL_Crypto.o $(LIBS_PATH)GOL_RNG.o

# Tests
TESTS = Test_Speed.run Test_RNG.run Test_GOL.run Test_CGOL.run

Tests: $(TESTS)

$(LIBS_PATH)%.o: ./src/%.cpp ./headers/%.h
	$(CC) $(LF) -o $@ $<
	
Test_%.run: Test_%.cpp $(OBJS)
	$(CC) -o $@ $< $(OBJS)

clean:
	rm *.run $(LIBS_PATH)*.o

# Dependency Chains
$(LIBS_PATH)BitBoard.o:   $(SRC_PATH)BitBoard.cpp $(H_PATH)BitBoard.h
$(LIBS_PATH)GOL.o:        $(LIBS_PATH)BitBoard.o $(SRC_PATH)GOL.cpp $(H_PATH)GOL.h
$(LIBS_PATH)GOL_Crypto.o: $(LIBS_PATH)GOL.o $(SRC_PATH)GOL_Crypto.cpp $(H_PATH)GOL_Crypto.h
$(LIBS_PATH)GOL_RNG.o:    $(LIBS_PATH)GOL_Crypto.o $(SRC_PATH)GOL_RNG.cpp $(H_PATH)GOL_RNG.h
