#ifndef GOL_B_Enc_H
#define GOL_B_Enc_H

#include "CCA_Board.h"
#include "CCA_Hash.h"
#include <fstream>
#include <filesystem>

class CCA_B_Enc 
{
    static const short BLOCK_SIZE = 512;
    unsigned long input_size;
    Bit_Board<u_int64_t> buffer;
    unsigned int seed;

    void scramble(CCA_Board* gol_board, Bit_Board<u_int64_t> key);

    public:

    CCA_B_Enc();

    CCA_B_Enc(std::string key);

    int encrypt(std::string in_path, std::string out_path);
    int decrypt(std::string in_path, std::string out_path);
};
#endif