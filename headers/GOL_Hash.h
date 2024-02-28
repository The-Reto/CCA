#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "Cryptographic_GOL_Board.h"
#include <fstream>
#include <filesystem>
#include <boost/algorithm/hex.hpp>

class GOL_Hash {
    
    public:

    Cryptographic_GOL_Board gol_board;
    u_int64_t salt[64];
    std::basic_ifstream<char> input_stream;
    unsigned long input_size;
    bool hashed, salted;
    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1, SALT_STEPS = 64;
    
    void hashing();
    
    GOL_Hash(std::string _path);
    
    auto get_input_stream();
    
    void set_salt();
    u_int64_t* get_salt();
    
    void print_graph_Hash();
    std::string get_Str_Hash();
    
};
#endif
