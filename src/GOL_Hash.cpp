#include "../headers/GOL_Hash.h"

GOL_Hash::GOL_Hash(std::string _path) : gol_board(0), input_stream(_path), hashed(false), salted(false) {
    input_size = std::filesystem::file_size(_path);
}

void GOL_Hash::fold() {
    for (int i =  0; i < SIZE_Y/2; i++) {
        gol_board.board[0][i] ^= gol_board.board[0][SIZE_Y-1-i];
        gol_board.board[0][i] ^= gol_board.board[0][i] >> (SIZE_X /2);
    }
}

void GOL_Hash::hashing() {
    hashed = true;
    u_int64_t data[64];
    const long bufferSize = std::min((int)input_size, (int)HASH_SIZE);
    while (!input_stream.eof()) {
        input_stream.read((char*) data, bufferSize);
        gol_board.apply_xor_map(data);
        gol_board.steps(BLOCK_STEPS);
    }
    if (salted) {gol_board.apply_xor_map(salt);}
    gol_board.steps(SALT_STEPS);
    fold();
}

void GOL_Hash::print_graph_Hash() {
    if (!hashed) {hashing();}
    // gol_board.visualize();
    std::cout << "VISUAL HASH CURRENTLY DISABLED" << std::endl;
}

void GOL_Hash::set_salt(u_int64_t _salt[64]) {
    for (int i = 0; i < 64; i++) {
        salt[i] = _salt[i];
    }
}

u_int64_t* GOL_Hash::get_salt() {
    return &salt[0];
}

std::string GOL_Hash::get_Str_Hash() {
    const static char symbols[65] = "0123456789ABCDFEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz:;";
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

std::bitset<1024> GOL_Hash::get_Hash() {
    if (!hashed) {hashing();}
    std::string buffer;
    for (int i = 0; i<SIZE_Y/2; i++) {
        buffer += std::bitset<SIZE_X /2>(gol_board.board[0][i]).to_string();
    }
    return std::bitset<1024>(buffer);
}