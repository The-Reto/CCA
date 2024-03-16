#ifndef GOL_Enc_H
#define GOL_Enc_H

#include "Cryptographic_GOL_Board.h"
#include "GOL_Keygen.h"
#include <fstream>
#include <filesystem>

class GOL_Enc 
{

    static const short BLOCK_SIZE = 512;
    unsigned long input_size;
    std::basic_ifstream<char> input_stream;
    std::basic_ofstream<char> output_stream;
    Bit_Board<u_int64_t> buffer, key;
    GOL_Keygen key_manager;
    bool run_once = false;
    
    void scramble_block(int blockSize);
    
    void encdec(std::string in_path, std::string out_path);
    
    public:
    
    GOL_Enc(std::string key);
    
    int encrypt(std::string in_path, std::string out_path);
    
};
#endif
