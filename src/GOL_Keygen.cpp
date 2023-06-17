#include "../headers/GOL_Keygen.h"

GOL_Keygen::GOL_Keygen(boost::dynamic_bitset<unsigned char> key_) : key(key_), gol_board(SIZE_X,SIZE_Y,0) {
    setup();
}

GOL_Keygen::GOL_Keygen(std::string key_) : gol_board(SIZE_X,SIZE_Y,0) {
    for (unsigned char c : key_) { key.append(c);}
    setup();
}

void GOL_Keygen::setup() {
    BitBoard start(SIZE_X,SIZE_Y);
    start.set(key);
    gol_board.apply_xormap(start);
    gol_board.steps(SIZE_X);
}

boost::dynamic_bitset<unsigned char> GOL_Keygen::get_streched_key(unsigned long len) { 
    gol_board.steps(BLOCK_STEPS);
    key = gol_board.get_board().get();
    if (len > SIZE_X*SIZE_Y) {
        key.resize(len);
        boost::dynamic_bitset<unsigned char> temp;
        for (int i = SIZE_X*SIZE_Y; i < len; i++) {
            if (i % (SIZE_Y*SIZE_X) == 0) {
                gol_board.steps(BLOCK_STEPS);
                temp = gol_board.get_board().get();
            }
            key.set(i, temp[ i % (SIZE_X*SIZE_Y) ]);
        }
    }
    else if (len < SIZE_X*SIZE_Y) { key.resize(len); }
    return key;
}
