# Compiler
CC = g++

# Lib Flags
LF = -c

# Paths
LIBS_PATH = ./lib/
SRC_PATH = ./src/
H_PATH = ./headers/
T_PATH = ./tests/
EXEC_PATH = ./execs/

# Tests
TESTS = $(EXEC_PATH)Test_Speed.run $(EXEC_PATH)Test_RNG.run $(EXEC_PATH)Test_GOL.run $(EXEC_PATH)Test_CGOL.run $(EXEC_PATH)Test_Hash.run

Tests: $(TESTS)

$(LIBS_PATH)%.o: $(SRC_PATH)%.cpp $(H_PATH)%.h
	$(CC) $(LF) -o $@ $<
	
$(EXEC_PATH)Test_%.run: $(T_PATH)Test_%.cpp
	$(CC) -o $@ $+

clean:
	rm $(EXEC_PATH)*.run $(LIBS_PATH)*.o

# Dependency Variables
GOL = $(LIBS_PATH)BitBoard.o $(LIBS_PATH)GOL.o
CGOL = $(GOL) $(LIBS_PATH)C_GOL.o

# Dependency Chains
$(EXEC_PATH)Test_GOL.run:	 $(GOL)
$(EXEC_PATH)Test_CGOL.run:	 $(CGOL)
$(EXEC_PATH)Test_RNG.run:    $(CGOL) $(LIBS_PATH)GOL_RNG.o
$(EXEC_PATH)Test_Hash.run:   $(CGOL) $(LIBS_PATH)GOL_Hash.o
$(EXEC_PATH)Test_Speed.run:  $(CGOL) $(LIBS_PATH)GOL_RNG.o $(LIBS_PATH)GOL_Hash.o
