#include "../headers/GOL_Hash.h"

GOL_Hash::GOL_Hash(std::ifstream & input_s) : system(SIZE_X,SIZE_Y,0), salt(SIZE_X,SIZE_Y), input_stream(input_s), hashed(false), salted(false) {
    
}

void GOL_Hash::salted_hashing() {
    hashed = true;
    BitBoard data(SIZE_X,SIZE_Y);
    std::vector<char> bytes(HASH_SIZE);
    while (!input_stream.eof()) {
        input_stream.read(bytes.data(), bytes.size());
        data.set(boost::dynamic_bitset<unsigned char>(bytes.begin(), bytes.end()));
        system.apply_xormap(data);
        system.steps(SIZE_X / 4);
        system.apply_xormap(salt);
        system.steps(SIZE_X / 4);
    }
}

void GOL_Hash::unsalted_hashing() {
    hashed = true;
    BitBoard data(SIZE_X,SIZE_Y);
    std::vector<char> bytes(HASH_SIZE);
    while (!input_stream.eof()) {
        input_stream.read(bytes.data(), bytes.size());
        data.set(boost::dynamic_bitset<unsigned char>(bytes.begin(), bytes.end()));
        system.apply_xormap(data);
        system.steps(SIZE_X / 2);
    }
}

void GOL_Hash::hashing() {
    if (salted) {salted_hashing();}
    else {unsalted_hashing();}
}

BitBoard GOL_Hash::get_Hash() {
    if (hashed) {return system.get_board();}
    hashing();
    return system.get_board();
}
