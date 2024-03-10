#include "../headers/GOL_B_Enc.h"

GOL_B_Enc::GOL_B_Enc(std::string key) {
    seed = 0;
    for (int i = 0; i < key.length(); i++) {
        seed += ((u_int64_t) key[i]) << (8*i % 64);
    }
}

void GOL_B_Enc::scramble(Cryptographic_GOL_Board* gol_board)
{
    (*gol_board).steps(16);
    for (int i = 0; i < 64; i+=2) { 
            (*gol_board).board[0][i] = (*gol_board).board[0][i]<<16;
            (*gol_board).board[0][i+1] = (*gol_board).board[0][i+1]>>16;
    }
    (*gol_board).steps(16);
}

void GOL_B_Enc::encrypt(std::string path) {
    Cryptographic_GOL_Board gol_board(seed);
    GOL_Hash hash(path);
    hash.hashing();
    // std::cout<< hash.get_Str_Hash() << std::endl;
    u_int64_t key_map[64];
    for (int i = 0; i<64; i++) {key_map[i] = gol_board.board[0][i];}
    u_int64_t hash_map[64];
    for (int i = 0; i<64; i++) {hash_map[i] = hash.gol_board.board[0][i];}

    std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(path);
    input_size = std::filesystem::file_size(path);
    std::string out_path = path;
    out_path.replace(out_path.size()-4, 1, "-");
    std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path+".trc", std::ios::binary );

    for (int i = 0; i < 64; i++) { 
            gol_board.board[0][i] = hash_map[i]^key_map[i];
    }
    output_stream.write(reinterpret_cast<char*>(&gol_board.board[0][0]), 64 * sizeof(u_int64_t));
    scramble(&gol_board);

    while (input_size >= BLOCK_SIZE) {
        input_stream.read(reinterpret_cast<char*>(&buffer[0]), BLOCK_SIZE);
        for (int i = 0; i < 64; i++) { 
            buffer[i] ^= key_map[i] ^ gol_board.board[0][i];
        }
        output_stream.write(reinterpret_cast<char*>(&buffer[0]), 64 * sizeof(u_int64_t));
        gol_board.set_board(buffer);
        scramble(&gol_board);
        input_size -= BLOCK_SIZE;
    }
    if (input_size > 0) {
        input_stream.read(reinterpret_cast<char*>(&buffer[0]), input_size);
        for (int i = 0; i < 64; i++) { 
            buffer[i] ^= key_map[i] ^ gol_board.board[0][i];
        }
        output_stream.write(reinterpret_cast<char*>(&buffer[0]), input_size * sizeof(unsigned char));  
    }
    input_stream.close();
    output_stream.close();
    GOL_Hash hash_enc(out_path+".trc");
    // std::cout<< hash_enc.get_Str_Hash() << std::endl;
}

void GOL_B_Enc::decrypt(std::string path) {
    Cryptographic_GOL_Board gol_board(seed);
    Bit_Board<u_int64_t> key_map, in_buffer;
    for (int i = 0; i<64; i++) {key_map[i] = gol_board.board[0][i];}
    u_int64_t hash_map[64];

    std::basic_ifstream<char>  input_stream = std::basic_ifstream<char>(path);
    input_size = std::filesystem::file_size(path) - BLOCK_SIZE;
    std::string out_file = path.substr(0, path.size()-8);
    std::string out_ext = path.substr(path.size()-7, 3);
    std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_file + "-DEC." + out_ext, std::ios::binary);

    input_stream.read(reinterpret_cast<char*>(&gol_board.board[0][0]), BLOCK_SIZE);
    for (int i = 0; i < 64; i++) { 
        hash_map[i] = key_map[i] ^  gol_board.board[0][i];
    }
    scramble(&gol_board);
    while (input_size >= BLOCK_SIZE) {
        input_stream.read(reinterpret_cast<char*>(&in_buffer[0]), BLOCK_SIZE);
        for (int i = 0; i < 64; i++) { 
            buffer[i] = in_buffer[i] ^ key_map[i] ^ gol_board.board[0][i];
        }
        gol_board.set_board(in_buffer);
        scramble(&gol_board);
        output_stream.write(reinterpret_cast<char*>(&buffer[0]), 64 * sizeof(u_int64_t));
        input_size -= BLOCK_SIZE;
    }
    if (input_size > 0) {
        input_stream.read(reinterpret_cast<char*>(&in_buffer[0]), input_size);
        for (int i = 0; i < 64; i++) { 
            buffer[i] = in_buffer[i] ^ key_map[i] ^ gol_board.board[0][i];
        }
        output_stream.write(reinterpret_cast<char*>(&buffer[0]), input_size * sizeof(unsigned char));  
    }

    input_stream.close();
    output_stream.close();
    
    GOL_Hash hash(out_file + "-DEC." + out_ext);
    hash.hashing();
    // std::cout << "Decrypted File has hash:" << std::endl;
    // std::cout << hash.get_Str_Hash() << std::endl;
    bool match = true;
    for (int i = 0; i<64; i++) {
        if (hash_map[i] != hash.gol_board.board[0][i]) {
            match = false;
            break;
        }
    }
    // if (match) {
    //     std::cout << "Which matches the check-sum of the original file.\nDECRYPTION SUCCESSFUL" << std::endl;
    // }
    // else {
    //     std::cout << "Which does not match the check-sum of the original file.\nDECRYPTION FAILED" << std::endl;
    // }
}