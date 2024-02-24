#include "../../headers/New_Implementation/Cryptographic_GOL_Board.h"

void Cryptographic_GOL_Board::step() {
    update_msb_lsb();
    update_GOL_board();
}

void Cryptographic_GOL_Board::update_GOL_board() {
    u_int64_t lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
    for (int i = 0; i < size; i++) {
        lsb_o = board[(i+size-1)%size][1];  msb_o = board[(i+size-1)%size][2];
        lsb_c = board[i][1];                msb_c = board[i][2];
        lsb_u = board[(i+1)%size][1];       msb_u = board[(i+1)%size][2];
        m = board[i][0];
        board[i][0] = ~m & // create new life where current board is empty IF:
        ( 
            ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
            (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
            ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
            (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) | // 4 neigbours : 2 msb set, no lsb set
            ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
            ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) // 5 neigbours : 1 msb, 3 lsb
        );
        t = msb_c & lsb_c; // for survival msb_ lsb_c will be one higher than needed as the base bit is counted
        lsb_c = msb_c & ~lsb_c;
        msb_c = t;
        board[i][0] |= m & // survive where current board is full IF:
        (
            ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
            ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) | // 3 neigbours : all lsb set, all msb unset
            ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
            ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) // 5 neigbours : 1 msb, 3 lsb
        );
    }
}

inline bool Cryptographic_GOL_Board::get(int index) {
    return GOL_Board<u_int64_t, 64>::get(index % 64, index / 64);
}