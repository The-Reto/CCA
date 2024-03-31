#include <fstream>
#include <filesystem>
#include <array>
#include <bitset>
#include <iostream>
#include <string.h>

const static int BLOCK_SIZE = 24 * 7;
const static char symbols[65] = "0123456789ABCDFEGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz<>";

void encode(std::string in_path, std::string out_path) {
    unsigned long input_size = std::filesystem::file_size(in_path);
    std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(in_path);
    std::ofstream output_stream(out_path);
    char * buffer;
    std::bitset<6> digit;
    std::bitset<BLOCK_SIZE * 8> reader;
    buffer = new char [BLOCK_SIZE];
    output_stream << "FILE-SIZE: " << input_size << "\n";
    int size = (input_size < BLOCK_SIZE) ? input_size : BLOCK_SIZE;
    while (input_size > 0) {
        input_stream.read(buffer, size);
        for(int i = 0; i < size; ++i)
        {
            uint8_t cur = buffer[i];
            int offset = i * 8;

            for(int bit = 0; bit < 8; ++bit)
            {
                reader[offset] = cur & 1;
                ++offset;
                cur >>= 1; 
            }
        }

        std::stringstream result;
        int count = 0;
        while (count < size * 8) {
            for (int i = 0; i < 6; i++) {
                digit.set(i, reader.test(count + i));
            }
            count += 6;
            result << symbols[digit.to_ulong()];
        }
        output_stream << result.str() << "\n";
        input_size -= size;
        size = (input_size < BLOCK_SIZE) ? input_size : BLOCK_SIZE;
    }

    input_stream.close();
    output_stream.close();
}

short get_bits(char c) {
    for (short i = 0; i<65; i++) {
        if (symbols[i] == c) {return i;}
    }
    return -1;
}

void decode(std::string in_path, std::string out_path) {
    std::string line;
    std::ifstream myfile (in_path);
    std::ofstream output(out_path);
    std::bitset<8*BLOCK_SIZE> bits;
    getline(myfile,line);
    long filesize = std::stol(line.substr(11, size(line)));
    while ( getline(myfile,line) ) {
        for (int i = 0; i < size(line); i++) {
            short c = get_bits(line[i]);
            for (int j = 0; j < 6; j++) {
                bits.set(6*i + j, c & (0b1 << j));
            }
        }
        output.write( reinterpret_cast<char *>(&bits), (filesize < BLOCK_SIZE) ? filesize : BLOCK_SIZE);
        filesize -= BLOCK_SIZE;
    }
    myfile.close();
    output.close();
}

int main(int argc, char *argv[]){ 
    if ( strcmp(argv[1], "-h") == 0 ) {
        std::cout << "USAGE: CA_6Bit_Enc {mode} {input_file} {output_file}\n Mode: either '-e' for encoding or '-d' for decoding\n input/output_file path to the input / output file\n" << std::endl;
        return 0;
    }
    std::string in_path = argv[2];
    std::string out_path = argv[3];
    if ( strcmp(argv[1], "-e") == 0 ) {
        encode(in_path, out_path);
    }
    else if ( strcmp(argv[1], "-d") == 0 ) {
        decode(in_path, out_path);
    }
    return 0;
}