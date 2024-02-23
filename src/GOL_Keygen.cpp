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
    key = gol_board.dynamic_rand_bits<SIZE_X * SIZE_X /2>();
    if (len > SIZE_X * SIZE_X /2) {
        key.resize(len);
        boost::dynamic_bitset<unsigned char> temp;
        for (int i = SIZE_X * SIZE_X /2; i < len; i++) {
            if (i % SIZE_X * SIZE_X /2 == 0) {
                temp = gol_board.dynamic_rand_bits<SIZE_X * SIZE_X /2>();
            }
            key.set(i, temp[ i % (SIZE_X*SIZE_Y) ]);
        }
    }
    else if (len < SIZE_X * SIZE_X /2) { key.resize(len); }
    return key;
}
