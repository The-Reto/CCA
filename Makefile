# Compiler
CC = g++

# Lib Flags
LF = -c
LIBS_PATH = ./lib/
SRC_PATH = ./src/
H_PATH = ./headers/
T_PATH = ./tests/
EXEC_PATH = ./execs/

# Objects
OBJS = $(LIBS_PATH)BitBoard.o $(LIBS_PATH)GOL.o $(LIBS_PATH)C_GOL.o $(LIBS_PATH)GOL_RNG.o $(LIBS_PATH)GOL_Hash.o

# Tests
TESTS = $(EXEC_PATH)Test_Speed.run $(EXEC_PATH)Test_RNG.run $(EXEC_PATH)Test_GOL.run $(EXEC_PATH)Test_CGOL.run $(EXEC_PATH)Test_Hash.run

Tests: $(TESTS)

$(LIBS_PATH)%.o: ./src/%.cpp ./headers/%.h
	$(CC) $(LF) -o $@ $<
	
$(EXEC_PATH)Test_%.run: $(T_PATH)Test_%.cpp $(OBJS)
	$(CC) -o $@ $< $(OBJS)

clean:
	rm $(EXEC_PATH)*.run $(LIBS_PATH)*.o

# Dependency Chains
$(LIBS_PATH)BitBoard.o:     $(SRC_PATH)BitBoard.cpp $(H_PATH)BitBoard.h
$(LIBS_PATH)GOL.o:          $(LIBS_PATH)BitBoard.o $(SRC_PATH)GOL.cpp $(H_PATH)GOL.h
$(LIBS_PATH)C_GOL.o:        $(LIBS_PATH)GOL.o $(SRC_PATH)C_GOL.cpp $(H_PATH)C_GOL.h
$(LIBS_PATH)GOL_RNG.o:      $(LIBS_PATH)C_GOL.o $(SRC_PATH)GOL_RNG.cpp $(H_PATH)GOL_RNG.h
$(LIBS_PATH)GOL_Hash.o:     $(LIBS_PATH)C_GOL.o $(SRC_PATH)GOL_Hash.cpp $(H_PATH)GOL_Hash.h
