#ifndef GOL_B_Enc_H
#define GOL_B_Enc_H

#include "Cryptographic_GOL_Board.h"
#include "GOL_Hash.h"
#include <fstream>
#include <filesystem>

class GOL_B_Enc 
{
    static const short BLOCK_SIZE = 512;
    unsigned long input_size;
    Bit_Board<u_int64_t> buffer;
    unsigned int seed;

    void scramble(Cryptographic_GOL_Board* gol_board, Bit_Board<u_int64_t> key);

    public:

    GOL_B_Enc();

    GOL_B_Enc(std::string key);

    int encrypt(std::string in_path, std::string out_path);
    int decrypt(std::string in_path, std::string out_path);
};
#endif