#include "../headers/Cryptographic_GOL_Board.h"

void Cryptographic_GOL_Board::step() {
    update_msb_lsb();
    update_GOL_board();
}

void Cryptographic_GOL_Board::steps(int steps) {
    for (int i = 0; i< steps; i++) {step();}
}

Cryptographic_GOL_Board::Cryptographic_GOL_Board(unsigned int _seed) {
    seed = (u_int64_t) _seed;
    for (int i = 0; i<size; i++) {board[i][0] = 0;}
    create_seed_map();
    steps(64);
}

void Cryptographic_GOL_Board::update_GOL_board() {
    u_int64_t lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
    for (int i = 0; i < size; i++) {
        m = board[i][0];
        lsb_o = board[(i+size-1)%size][1];  msb_o = board[(i+size-1)%size][2];
        lsb_c = (~m&board[i][1])|(m&(board[i][2]&~board[i][1]));
        msb_c = (board[i][2]&board[i][1])|(board[i][2]&~m);
        lsb_u = board[(i+1)%size][1];       msb_u = board[(i+1)%size][2];
        board[i][0] = ~m & // create new life where current board is empty IF:
        ( 
            ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
            (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
            ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
            (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) | // 4 neigbours : 2 msb set, no lsb set
            ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
            ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) // 5 neigbours : 1 msb, 3 lsb
        ) | m & // survive where current board is full IF:
        (
            ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
            ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) | // 3 neigbours : all lsb set, all msb unset
            ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
            ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) // 5 neigbours : 1 msb, 3 lsb
        );
    }
}

void Cryptographic_GOL_Board::create_seed_map() {
    const static int multipliers[3] = {5,127,2293}; //Prime Number No. 3,31,314
    for (int i : multipliers) {
        for (int y = 0; y < size; y++) {
            board[y][0] = std::rotr(seed, (i+y*i) % size);
        }
    }
}

void Cryptographic_GOL_Board::apply_xor_map(u_int64_t xor_map[size]) {
    for (int i =0; i<size; i++) {
        board[i][0] ^= xor_map[i];
    }
}

void Cryptographic_GOL_Board::set_seed(u_int64_t _seed) {
    seed = _seed;
}