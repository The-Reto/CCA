#include "../../headers/CCA_Hash.h"
#include <iostream>


CCA_Hash::CCA_Hash(std::istream &input_stream, unsigned long input_size): gol_board(0) {
    u_int64_t data[64] = {0};
    long bufferSize = std::min((int)input_size, (int)HASH_SIZE);
    while (input_size > 0) {
        input_stream.read((char*) data, bufferSize);
        gol_board.apply_xor_map(data);
        gol_board.steps(BLOCK_STEPS);
        input_size -= bufferSize;
        bufferSize = std::min((int)input_size, (int)HASH_SIZE);
    }
    gol_board.steps(MIX_STEPS);
}

void CCA_Hash::print_graph_Hash() {
    std::cout << get_graph_Hash() << std::endl;

}

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

std::string CCA_Hash::get_Str_Hash() {
    const static char symbols[65] = "0123456789ABCDFEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+_";
    std::stringstream reader(get_Hash().to_string());
    std::stringstream result;

    std::bitset<6> digit;
    while (reader) {
        reader >> digit;
        result << symbols[digit.to_ulong()];
        digit.reset();
    }
    std::string res = result.str();
    return res.substr(0, res.size()-1);
}

std::bitset<2048> CCA_Hash::get_Hash() {
    std::string buffer;
    for (int i = 0; i<SIZE_Y/ 2; i++) {
        buffer += std::bitset<SIZE_X>(gol_board[0][i] ^ gol_board[0][SIZE_Y/ 2 + i]).to_string();
    }
    return std::bitset<2048>(buffer);
}