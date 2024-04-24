#include "../../headers/CCA_Keygen.h"

CCA_Keygen::CCA_Keygen(std::string key_) : gol_board(0) {
    u_int64_t seed = 0;
    for (int i = 0; i < key_.length(); i++) {
        seed += ((u_int64_t) key_[i]) << (8*i % 64);
    }
    gol_board.set_seed(seed);
    gol_board.create_seed_map();
    gol_board.steps(SIZE_X);
}

void CCA_Keygen::setup() {

}

Bit_Board<u_int64_t> CCA_Keygen::get_streched_key() { 
    key = gol_board[0];
    gol_board.step();
    return key;
}
