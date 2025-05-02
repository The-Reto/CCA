#include "../../headers/CCA_B_Enc.h"

CCA_B_Enc::CCA_B_Enc(std::string key) {
    seed = 0;
    for (int i = 0; i < key.length(); i++) {
        seed += ((u_int64_t) key[i]) << (8*i % 64);
    }
}

void CCA_B_Enc::scramble(CCA_Board* gol_board, Bit_Board<u_int64_t> key)
{
    (*gol_board).steps(2);
    for (int i = 0; i < 64; i+=2) { 
            (*gol_board)[0][i] = (*gol_board)[0][i]<<16 ^ key[i];
            (*gol_board)[0][i+1] = (*gol_board)[0][i+1]>>16 ^ key[i];
    }
    (*gol_board).steps(2);
}

int CCA_B_Enc::encrypt(std::string in_path, std::string out_path) {
    // CCA_Board gol_board(seed);
    // std::basic_ifstream<char> stream(in_path);
    // CCA_Hash hash(stream, std::filesystem::file_size(in_path));
    // Bit_Board<u_int64_t> key_map, hash_map;
    // for (int i = 0; i<64; i++) {key_map[i] = gol_board[0][i];}
    // for (int i = 0; i<64; i++) {hash_map[i] = hash.gol_board[0][i];}

    // std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(in_path);
    // input_size = std::filesystem::file_size(in_path);
    // std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path, std::ios::binary );

    // for (int i = 0; i < 64; i++) { 
    //         gol_board[0][i] = hash_map[i]^key_map[i];
    // }
    // output_stream.write(reinterpret_cast<char*>(&gol_board[0][0]), 64 * sizeof(u_int64_t));
    // scramble(&gol_board,key_map);

    // while (input_size >= BLOCK_SIZE) {
    //     input_stream.read(reinterpret_cast<char*>(&buffer[0]), BLOCK_SIZE);
    //     for (int i = 0; i < 64; i++) { 
    //         buffer[i] ^= key_map[i] ^ gol_board[0][i];
    //     }
    //     output_stream.write(reinterpret_cast<char*>(&buffer[0]), 64 * sizeof(u_int64_t));
    //     gol_board.set_board(buffer);
    //     scramble(&gol_board,key_map);
    //     input_size -= BLOCK_SIZE;
    // }
    // if (input_size > 0) {
    //     input_stream.read(reinterpret_cast<char*>(&buffer[0]), input_size);
    //     for (int i = 0; i < 64; i++) { 
    //         buffer[i] ^= key_map[i] ^ gol_board[0][i];
    //     }
    //     output_stream.write(reinterpret_cast<char*>(&buffer[0]), input_size * sizeof(unsigned char));  
    // }
    // input_stream.close();
    // output_stream.close();
    // return 0;
}

int CCA_B_Enc::decrypt(std::string in_path, std::string out_path) {
    // CCA_Board gol_board(seed);
    // Bit_Board<u_int64_t> key_map, in_buffer;
    // for (int i = 0; i<64; i++) {key_map[i] = gol_board[0][i];}
    // u_int64_t hash_map[64];

    // std::basic_ifstream<char>  input_stream = std::basic_ifstream<char>(in_path);
    // input_size = std::filesystem::file_size(in_path) - BLOCK_SIZE;
    // std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path, std::ios::binary);

    // input_stream.read(reinterpret_cast<char*>(&gol_board[0][0]), BLOCK_SIZE);
    // for (int i = 0; i < 64; i++) { 
    //     hash_map[i] = key_map[i] ^  gol_board[0][i];
    // }
    // scramble(&gol_board, key_map);
    // while (input_size >= BLOCK_SIZE) {
    //     input_stream.read(reinterpret_cast<char*>(&in_buffer[0]), BLOCK_SIZE);
    //     for (int i = 0; i < 64; i++) { 
    //         buffer[i] = in_buffer[i] ^ key_map[i] ^ gol_board[0][i];
    //     }
    //     gol_board.set_board(in_buffer);
    //     scramble(&gol_board, key_map);
    //     output_stream.write(reinterpret_cast<char*>(&buffer[0]), 64 * sizeof(u_int64_t));
    //     input_size -= BLOCK_SIZE;
    // }
    // if (input_size > 0) {
    //     input_stream.read(reinterpret_cast<char*>(&in_buffer[0]), input_size);
    //     for (int i = 0; i < 64; i++) { 
    //         buffer[i] = in_buffer[i] ^ key_map[i] ^ gol_board[0][i];
    //     }
    //     output_stream.write(reinterpret_cast<char*>(&buffer[0]), input_size * sizeof(unsigned char));  
    // }

    // input_stream.close();
    // output_stream.close();
    
    // std::basic_ifstream<char> stream(out_path);
    // CCA_Hash hash(stream, std::filesystem::file_size(out_path));
    // bool match = true;
    // for (int i = 0; i<64; i++) {
    //     if (hash_map[i] != hash.gol_board[0][i]) {
    //         match = false;
    //         break;
    //     }
    // }
    // if (match) {
    //     return 0;
    // }
    // else {
    //     return -1;
    // }
}