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
    u_int64_t buffer[64];
    unsigned int seed;

    void scramble(Cryptographic_GOL_Board* gol_board);

    public:

    GOL_B_Enc();

    GOL_B_Enc(std::string key);

    void encrypt(std::string path);
    void decrypt(std::string path);
};
#endif