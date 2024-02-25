#include "../headers/GOL_Keygen.h"

GOL_Keygen::GOL_Keygen(std::string key_) : gol_board(0) {
    for (unsigned char c : key_) { key.append(c);}
    setup();
}

void GOL_Keygen::setup() {
    u_int64_t seed = 0;
    std::string str;
    boost::to_string(key, str);
    for (int i = 0; i < str.length(); i++) {
        seed += ((u_int64_t) str[i]) << (8*i % 64);
    }
    gol_board.set_seed(seed);
    gol_board.create_seed_map();
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
