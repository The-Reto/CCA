#ifndef GOL_Enc_H
#define GOL_Enc_H

#include "CCA_Board.h"
#include "CCA_Keygen.h"
#include <fstream>
#include <filesystem>

class CCA_S_Enc 
{

    static const short BLOCK_SIZE = 512;
    Bit_Board<u_int64_t> buffer, key;
    CCA_Keygen key_manager;
    bool run_once = false;
    
    void scramble_block(std::basic_istream<char>* input_stream, int blockSize, std::basic_ostream<char>* output_stream);
        
    public:
    
    CCA_S_Enc(std::string key);
    
    int encrypt(std::string in_path, std::string out_path);

    void encdec(std::basic_istream<char>* input_stream, unsigned long input_size, std::basic_ostream<char>* output_stream);
    
};
#endif
