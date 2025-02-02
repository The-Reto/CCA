#include "../../headers/CCA_S_Enc.h"

CCA_S_Enc::CCA_S_Enc(std::string key) : key_manager(key) {}

void CCA_S_Enc::scramble_block(std::basic_istream<char>* input_stream, int blockSize, std::basic_ostream<char>* output_stream) {
    input_stream->read(reinterpret_cast<char*>(&buffer[0]), blockSize);
    key = key_manager.get_streched_key();
    for (int i = 0; i < 64; i++){
        buffer[i] ^= key[i];
    }
    output_stream->write(reinterpret_cast<char*>(&buffer[0]), blockSize * sizeof(unsigned char));
}


void CCA_S_Enc::encdec(std::basic_istream<char>* input_stream, unsigned long input_size, std::basic_ostream<char>* output_stream) {
    while (input_size >= BLOCK_SIZE) {
        scramble_block(input_stream, BLOCK_SIZE, output_stream);
        input_size -= BLOCK_SIZE;
    }
    if (input_size > 0) {
        scramble_block(input_stream, input_size, output_stream);
    }
}

int CCA_S_Enc::encrypt(std::string in_path, std::string out_path) {
    if (run_once) {
        std::cout << "already ran once, need to be reinitialized";
        return -1;
    }
    run_once = true;

    std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(in_path);
    unsigned long input_size = std::filesystem::file_size(in_path);
    std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path, std::ios::binary );
    encdec(&input_stream, input_size, &output_stream);
    input_stream.close();
    output_stream.close();
    return 0;
}

