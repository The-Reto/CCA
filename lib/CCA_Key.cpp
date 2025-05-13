#include "../include/CCA_Key.h"
#include "../include/CCA_Hash.h"
#include "../include/BitBoardStringReader.h"
#include <random>
#include <fstream>
#include <bit>

CCA_Key::CCA_Key(Bit_Board<u_int64_t> _key) : CCA_Board() {
    set_board(_key);
}

Bit_Board<u_int64_t> *CCA_Key::get_streched_key()
{
    step();
    return &board[0];
}

Bit_Board<u_int64_t> *CCA_Key::get_key()
{
    return &board[0];
}

bool CCA_Key::write_key_to_file(CCA_Key key, std::string path)
{
    std::ofstream out(path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(&(key.board)), BIT_BOARD_STREAM_BUFFER_SIZE);
    return out.good();
}

CCA_Key CCA_Key::generate_key(std::string user_input)
{
    const static u_int64_t multipliers[3] = {2293,28843,368411}; //Prime Number No. 314, 3141, 31415
    Bit_Board<u_int64_t> new_key;
    std::random_device rd;
    std::uniform_int_distribution<u_int32_t> dist(0, 0xFFFFFFFF);
    u_int32_t seed = dist(rd);
    BitBoardStringReader stream(user_input);
    CCA_Hash hasher;
    stream.run(hasher);
    Bit_Board<u_int64_t> hash = hasher.get_Hash();
    for (int y = 0; y < size; y++) {
        new_key[y] ^= hash[y] ^ pi[y] ^ seed;
    } 
    CCA_Key to_ret = CCA_Key(new_key);
    to_ret.steps(32);
    for (u_int64_t i : multipliers) {
        for (int y = 0; y < size; y++) {
            to_ret.board[0][y] ^= std::rotr(seed, (y*i) % 32);
            to_ret.board[0][y] = std::rotl(to_ret.board[0][y], (seed*i*y) % size);
        }
        to_ret.steps(32);
        for (int y = 0; y < size; y++) {
            to_ret.board[0][y] ^= std::rotr(hash[i*y], (y*i) % size);
        }
    }
    
    return CCA_Key(new_key);
}

CCA_Key CCA_Key::read_key(std::string path)
{
    std::ifstream file(path, std::ios::binary);
    Bit_Board<u_int64_t> buffer;

    file.read(reinterpret_cast<char*>(&buffer), BIT_BOARD_STREAM_BUFFER_SIZE);

    return CCA_Key(buffer);
}
