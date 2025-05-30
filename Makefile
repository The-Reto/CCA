# Compiler
CC = g++ -std=c++2a

# Lib Flags
LF = -c
OPF = -O3

# Paths
SRC_PATH = ./src/
H_PATH = ./include/
T_PATH = ./tests/
L_PATH = ./lib/
EXEC_PATH = ./execs/
T_EXEC_PATH = $(EXEC_PATH)tests/
P_EXEC_PATH = $(EXEC_PATH)products/
LIBS_PATH = $(EXEC_PATH)lib/


# Tests
TESTS = $(T_EXEC_PATH)Test_Speed.run $(T_EXEC_PATH)Test_RNG.run $(T_EXEC_PATH)Test_Hash.run $(T_EXEC_PATH)Test_Key.run $(T_EXEC_PATH)Test_S_Enc.run $(T_EXEC_PATH)Test_CA_Board.run $(T_EXEC_PATH)Test_B_Enc.run $(T_EXEC_PATH)Test_BitBoard.run $(T_EXEC_PATH)Test_Dieharder.run $(T_EXEC_PATH)Test_Wipe.run  
#$(T_EXEC_PATH)Test_Cycle_Len.run $(T_EXEC_PATH)Test_Archive.run  

LIBS = $(LIBS_PATH)CCA_S_Enc.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_RNG.o $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_B.o $(LIBS_PATH)CCA_B_Dec.o $(LIBS_PATH)CCA_B_Enc.o $(LIBS_PATH)CCA_Wiper.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)BitBoardStringReader.o $(LIBS_PATH)6BitEncoder.o
#$(LIBS_PATH)CCA_Archive.o

PRODUCTS = $(P_EXEC_PATH)CCA_Encrypt.run $(P_EXEC_PATH)CCA_Hash.run $(P_EXEC_PATH)CCA_Wipe.run $(P_EXEC_PATH)CCA_Key_Generator.run

default: Libs Tests

clean:
	rm $(T_EXEC_PATH)*.run $(P_EXEC_PATH)*.run $(LIBS_PATH)*.o ./test_data/*.trc

install: Products
	sudo cp $(P_EXEC_PATH)CCA_Encrypt.run /usr/bin/ccaenc
	sudo cp $(P_EXEC_PATH)CCA_Hash.run /usr/bin/ccahash
	sudo cp $(P_EXEC_PATH)CCA_Wipe.run /usr/bin/ccawipe
	sudo cp $(P_EXEC_PATH)CCA_Key_Generator.run /usr/bin/ccakey

All: Libs Tests Products

Libs: $(LIBS)

Tests: $(TESTS)

Products: $(PRODUCTS)

$(LIBS_PATH)%.o: $(L_PATH)%.cpp $(H_PATH)%.h
	$(CC) $(LF) -o $@ $(OPF) $<

$(T_EXEC_PATH)Test_%.run: $(T_PATH)Test_%.cpp
	$(CC) -o $@ $(OPF) $+

$(P_EXEC_PATH)CCA_%.run: $(SRC_PATH)CCA_%.cpp
	$(CC) -o $@ $(OPF) $+


# Dependency Chains
$(T_EXEC_PATH)Test_CA_Board.run: 
$(T_EXEC_PATH)Test_BitBoard.run: 
$(T_EXEC_PATH)Test_RNG.run:    $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_RNG.o
$(T_EXEC_PATH)Test_Hash.run:   $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_Key.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_S_Enc.run:    $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)CCA_S_Enc.o $(LIBS_PATH)BitBoardFileReader.o  $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_Speed.run:  $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_RNG.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_B.o $(LIBS_PATH)CCA_B_Enc.o $(LIBS_PATH)CCA_B_Dec.o $(LIBS_PATH)CCA_S_Enc.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_B_Enc.run:  $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)CCA_B.o $(LIBS_PATH)CCA_B_Enc.o $(LIBS_PATH)CCA_B_Dec.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_Dieharder.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o  $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_Wipe.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_Wiper.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o
$(T_EXEC_PATH)Test_Archive.run: $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)CCA_S_Enc.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Archive.o

$(P_EXEC_PATH)CCA_Encrypt.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_S_Enc.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)CCA_B_Enc.o $(LIBS_PATH)CCA_B_Dec.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)BitBoardOSink.o  $(LIBS_PATH)CCA_B.o $(LIBS_PATH)BitBoardStringReader.o
$(P_EXEC_PATH)CCA_Hash.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardFileReader.o $(LIBS_PATH)BitBoardOSink.o $(LIBS_PATH)BitBoardStringReader.o $(LIBS_PATH)6BitEncoder.o
$(P_EXEC_PATH)CCA_Wipe.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_Wiper.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o
$(P_EXEC_PATH)CCA_Key_Generator.run: $(LIBS_PATH)CCA_Board.o $(LIBS_PATH)CCA_Key.o $(LIBS_PATH)CCA_Hash.o $(LIBS_PATH)BitBoardStringReader.o