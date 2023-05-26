#include "../headers/GOL_Keygen.h"

GOL_Keygen::GOL_Keygen(boost::dynamic_bitset<unsigned char> key_) : key(key_), gol_board(SIZE_X,SIZE_Y,0), salt(SIZE_X,SIZE_Y, 3141592) {
    setup();
}

GOL_Keygen::GOL_Keygen(std::string key_) : gol_board(SIZE_X,SIZE_Y,0), salt(SIZE_X,SIZE_Y, 3141592) {
    for (unsigned char c : key_) { key.append(c);}
    setup();
}

void GOL_Keygen::setup() {
    BitBoard start(SIZE_X,SIZE_Y);
    start.set(key);
    gol_board.apply_xormap(start);
    gol_board.steps(SIZE_X);
    salt.steps(SIZE_X);
}

boost::dynamic_bitset<unsigned char> GOL_Keygen::get_streched_key(unsigned long len) {
    boost::dynamic_bitset<unsigned char> temp = gol_board.get_board().get() ^ salt.get_board().get();
    key.resize(len);
    for (int i = 0; i < len; i++) {
        key.set(i, temp[ (5*i) % (SIZE_X*SIZE_Y) ]);
        if (i % (2*SIZE_X) == 0) {
            gol_board.steps(5);
            salt.steps(1);
            temp = gol_board.get_board().get() ^ salt.get_board().get();
        }
    }
    return key;
}
