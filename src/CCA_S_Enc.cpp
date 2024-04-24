#include "../headers/CCA_S_Enc.h"

CCA_S_Enc::CCA_S_Enc(std::string key) : key_manager(key) {}

void CCA_S_Enc::scramble_block(int blockSize) {
    input_stream.read(reinterpret_cast<char*>(&buffer[0]), blockSize);
    key = key_manager.get_streched_key();
    for (int i = 0; i < 64; i++){
        buffer[i] ^= key[i];
    }
    output_stream.write(reinterpret_cast<char*>(&buffer[0]), blockSize * sizeof(unsigned char));
}


void CCA_S_Enc::encdec(std::string in_path, std::string out_path) {
    input_stream = std::basic_ifstream<char>(in_path);
    input_size = std::filesystem::file_size(in_path);
    output_stream = std::basic_ofstream<char>(out_path, std::ios::binary );
    while (input_size >= BLOCK_SIZE) {
        scramble_block(BLOCK_SIZE);
        input_size -= BLOCK_SIZE;
    }
    if (input_size > 0) {
        scramble_block(input_size);
    }
    input_stream.close();
    output_stream.close();
}

int CCA_S_Enc::encrypt(std::string in_path, std::string out_path) {
    if (run_once) {
        std::cout << "already ran once, need to be reinitialized";
        return -1;
    }
    run_once = true;
    encdec(in_path, out_path);
    return 0;
}

