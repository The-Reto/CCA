#include "../../headers/CCA_Hash.h"
#include "../../headers/BitBoardDiscardSink.h"


CCA_Hash::CCA_Hash(BitBoardStreamBuf &_next) : next(_next), gol_board(0), hash_calculated(false) {}

CCA_Hash::CCA_Hash() : next(DISCARD_SINK), gol_board(0), hash_calculated(false) {}

bool CCA_Hash::put(Bit_Board<u_int64_t> buffer, int size) {
    if (!hash_calculated) {
        add_to_hash(buffer);
        return next.put(buffer, size);
    }
    return false;
}

void CCA_Hash::add_to_hash(Bit_Board<u_int64_t>& _buffer) {
    gol_board.apply_xor_map(_buffer);
    gol_board.steps(BLOCK_STEPS);
}

Bit_Board<u_int64_t> CCA_Hash::get_Hash() {
    if (!hash_calculated) {
        gol_board.steps(MIX_STEPS);
        hash_calculated = true;
    }
    return gol_board.get_board();
}

/*
std::string CCA_Hash::get_graph_Hash() {
    std::bitset<2048> hash = get_Hash();
    std::string to_ret = "\u250f\u2501";
    for (int i = 0; i < SIZE_X; i++) { to_ret += "\u2501\u2501"; }
    to_ret += "\u2513\n";
    for (int i = 0; i < SIZE_Y / 2; i++) {
        to_ret += "\u2503 ";
        for (int j = 0; j < SIZE_X; j++) {
            if (hash[32*i + j]) { to_ret += "\u25A0 "; }
            else { to_ret += "\u25A2 "; }
        }
        to_ret += "\u2503\n";
    }
    to_ret += "\u2517\u2501";
    for (int i = 0; i < SIZE_X; i++) { to_ret += "\u2501\u2501"; }
    to_ret += "\u251b\n";
    return to_ret;
}
*/