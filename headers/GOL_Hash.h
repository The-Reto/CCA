#ifndef GOL_HASH_H
#define GOL_HASH_H
#include "C_GOL.h"
#include "BitBoard.h"
#include <fstream>

class GOL_Hash {
    
    C_GOL system;
    BitBoard salt;
    std::ifstream &input_stream;
    bool hashed, salted;
    const static short HASH_SIZE = 256, SIZE_X = 32, SIZE_Y = 64;
    
    void salted_hashing();
    void unsalted_hashing();
    
    void hashing();
    
    public:
    GOL_Hash(std::ifstream & input_s);
    
    auto get_input_stream();
    
    void set_salt();
    BitBoard get_salt();
    
    BitBoard get_Hash();
    std::string get_Str_Hash();
    
};
#endif
