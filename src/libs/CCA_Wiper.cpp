#include "../../headers/CCA_Wiper.h"
#include <iostream>
#include <cstdio>


void CCA_Wiper::wipe(std::string path, std::string seed, short repetitions) {
    CCA_Keygen gol_board(seed); 
    Bit_Board<u_int64_t> key;
    unsigned long file_size = std::filesystem::file_size(path), input_size;
    std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(path, std::ios::binary | std::ios::trunc);
    for (int i = 0; i < repetitions; i++) {
        input_size = file_size;
        while (input_size >= BLOCK_SIZE) {
            key = gol_board.get_streched_key();
            output_stream.write(reinterpret_cast<char*>(&key[0]), BLOCK_SIZE * sizeof(unsigned char));
            input_size -= BLOCK_SIZE;
        }
        if (input_size > 0) {
            key = gol_board.get_streched_key();
            output_stream.write(reinterpret_cast<char*>(&key[0]), input_size * sizeof(unsigned char));
        }
        output_stream.flush();
        output_stream.seekp(0, std::ios_base::beg);
    }
    output_stream.close();
    std::remove(path.c_str());
}