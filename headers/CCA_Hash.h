#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "CCA_Board.h"
#include <fstream>
#include <boost/algorithm/hex.hpp>

class CCA_Hash {    
    public:
    CCA_Board gol_board;    

    CCA_Hash(std::string _path);
        
    void set_salt(u_int64_t _salt[64]);
    u_int64_t* get_salt();

    const static short SIZE_X = 64, SIZE_Y = 64, HASH_SIZE = SIZE_X * SIZE_Y / CHAR_BIT, BLOCK_STEPS = 1, MIX_STEPS = 64;    

    CCA_Hash(std::istream &input_stream, unsigned long input_size);
    
    void print_graph_Hash();
    std::string get_Str_Hash();
    std::string get_graph_Hash();
    std::bitset<2048> get_Hash();
    
};
#endif
