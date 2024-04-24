# Compiler
CC = g++ -std=c++2a

# Lib Flags
LF = -c
OPF = -O3

# Paths
LIBS_PATH = ./lib/
SRC_PATH = ./src/
H_PATH = ./headers/
T_PATH = ./tests/
EXEC_PATH = ./execs/
T_EXEC_PATH = ./execs/tests/

# Tests
TESTS = $(T_EXEC_PATH)Test_Speed.run $(T_EXEC_PATH)Test_RNG.run $(T_EXEC_PATH)Test_Hash.run $(T_EXEC_PATH)Test_Keygen.run $(T_EXEC_PATH)Test_Enc.run $(T_EXEC_PATH)Test_GOL_Board.run $(T_EXEC_PATH)Test_B_Enc.run $(T_EXEC_PATH)Test_BitBoard.run $(T_EXEC_PATH)Test_Dieharder.run $(T_EXEC_PATH)Test_Cycle_Len.run

LIBS = $(LIBS_PATH)GOL_Enc.o $(LIBS_PATH)GOL_Hash.o $(LIBS_PATH)GOL_Keygen.o $(LIBS_PATH)GOL_RNG.o $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_B_Enc.o

PRODUCTS = $(EXEC_PATH)CA_Encrypt.run

default: Libs Tests

Libs: $(LIBS)

Tests: $(TESTS)

Products: $(PRODUCTS)

$(LIBS_PATH)%.o: $(SRC_PATH)%.cpp $(H_PATH)%.h
	$(CC) $(LF) -o $@ $(OPF) $<

$(T_EXEC_PATH)Test_%.run: $(T_PATH)Test_%.cpp
	$(CC) -o $@ $(OPF) $+

$(EXEC_PATH)CA_%.run: $(SRC_PATH)CA_%.cpp
	$(CC) -o $@ $(OPF) $+

clean:
	rm $(EXEC_PATH)*.run $(LIBS_PATH)*.o ./test_data/*.trc


# Dependency Chains
$(T_EXEC_PATH)Test_GOL_Board.run: 
$(T_EXEC_PATH)Test_BitBoard.run: 
$(T_EXEC_PATH)Test_Cycle_Len.run: 
$(T_EXEC_PATH)Test_RNG.run:    $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_RNG.o
$(T_EXEC_PATH)Test_Hash.run:   $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Hash.o
$(T_EXEC_PATH)Test_Keygen.run: $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Keygen.o
$(T_EXEC_PATH)Test_Enc.run:    $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Keygen.o $(LIBS_PATH)GOL_Enc.o
$(T_EXEC_PATH)Test_Speed.run:  $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_RNG.o $(LIBS_PATH)GOL_Hash.o $(LIBS_PATH)GOL_Keygen.o $(LIBS_PATH)GOL_B_Enc.o $(LIBS_PATH)GOL_Enc.o
$(T_EXEC_PATH)Test_B_Enc.run:  $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Hash.o $(LIBS_PATH)GOL_B_Enc.o
$(T_EXEC_PATH)Test_Dieharder.run: $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Keygen.o
$(EXEC_PATH)CA_Encrypt.run: $(LIBS_PATH)Cryptographic_GOL_Board.o $(LIBS_PATH)GOL_Keygen.o $(LIBS_PATH)GOL_Enc.o $(LIBS_PATH)GOL_Hash.o $(LIBS_PATH)GOL_B_Enc.o