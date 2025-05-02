#include "../../headers/CCA_Board.h"

void CCA_Board::step() {
    update_msb_lsb();
    update_GOL_board();
}

void CCA_Board::steps(int steps) {
    for (int i = 0; i< steps; i++) {step();}
}

CCA_Board::CCA_Board(unsigned int _seed) {
    seed = (u_int64_t) _seed;
    for (int i = 0; i<size; i++) {board[0][i] = 0;}
    create_seed_map();
    steps(64);
}

CCA_Board::CCA_Board(): CCA_Board(0) {

}


void CCA_Board::update_GOL_board() {
    u_int64_t lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
    for (int i = 0; i < size; i++) {
        m = board[0][i];
        lsb_o = board[1][(i+size-1)%size];  msb_o = board[2][(i+size-1)%size];
        lsb_c = (~m&board[1][i])|(m&(board[2][i]&~board[1][i]));
        msb_c = (board[2][i]&board[1][i])|(board[2][i]&~m);
        lsb_u = board[1][(i+1)%size];       msb_u = board[2][(i+1)%size];
        board[0][i] = board[1][(i+2)%size] ^ (pi[i] & board[2][(i+size-2)%size]) ^ (
        ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours (happens independently of m) : two msb set, 1 lsb OR
        ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 5 neigbours : 1 msb, 3 lsb
        ~m & // create new life where current board is empty IF:
        ( 
            ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
            (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
            ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
            (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) // 4 neigbours : 2 msb set, no lsb set
        ) | m & // survive where current board is full IF:
        (
            ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
            ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) // 3 neigbours : all lsb set, all msb unset
        ));
    }
}

void CCA_Board::create_seed_map() {
    const static int multipliers[3] = {5,127,2293}; //Prime Number No. 3,31,314
    for (int y = 0; y < size; y++) {
        board[0][y] = pi[y];
    }
    for (int i : multipliers) {
        for (int y = 0; y < size/2; y++) {
            board[0][y] ^= std::rotr(seed, (i+y*i) % size);
        }
        for (int y = 0; y < size/2; y++) {
            board[0][size/2+y] ^= seed ^ (i+y*i);
        }
    }
}

void CCA_Board::apply_xor_map(Bit_Board<u_int64_t> xor_map) {
    for (int i =0; i<size; i++) {
        board[0][i] ^= xor_map[i];
    }
}

void CCA_Board::set_seed(u_int64_t _seed) {
    seed = _seed;
}