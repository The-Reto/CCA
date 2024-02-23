#ifndef GOL_Enc_H
#define GOL_Enc_H

#include "C_GOL.h"
#include "GOL_Keygen.h"
#include "BitBoard.h"
#include <fstream>
#include <filesystem>

class GOL_Enc 
{

    static const short BLOCK_SIZE = 256;
    unsigned long input_size;
    std::basic_ifstream<char> input_stream;
    std::basic_ofstream<char> output_stream;
    std::vector<char> buffer;
    GOL_Keygen key_manager;
    bool run_once = false;
    
    void scramble_block(int blockSize);
    
    void encdec(std::string in_path, std::string out_path);
    
    public:
    
    GOL_Enc(std::string key);
    
    void encrypt(std::string path);
    
    void decrypt(std::string path);

};
#endif
