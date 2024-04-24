#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "CCA_Board.h"
#include <fstream>
#include <filesystem>
#include <boost/algorithm/hex.hpp>

class CCA_Hash {

    void fold();
    
    public:

    CCA_Board gol_board;
    u_int64_t salt[64];
    std::basic_ifstream<char> input_stream;
    unsigned long input_size;
    bool hashed, salted;
    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1, SALT_STEPS = 64;
    
    void hashing();
    

    CCA_Hash(std::string _path);
        
    void set_salt(u_int64_t _salt[64]);
    u_int64_t* get_salt();
    
    void print_graph_Hash();
    std::string get_Str_Hash();
    std::string get_graph_Hash();
    std::bitset<1024> get_Hash();
    
};
#endif
