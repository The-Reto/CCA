#include "../../headers/CCA_Key.h"
#include "../../headers/CCA_Hash.h"
#include <random>
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
CCA_Key CCA_Key::generate_key(std::string user_input)
{
    const static u_int64_t multipliers[3] = {2293,28843,368411}; //Prime Number No. 314, 3141, 31415
    Bit_Board<u_int64_t> new_key;
    std::random_device rd;
    std::uniform_int_distribution<u_int32_t> dist(0, 0xFFFFFFFF);
    u_int64_t seed = dist(rd);
    std::istringstream stream(user_input);
    CCA_Hash hasher(stream, std::strlen(user_input.c_str()));
    Bit_Board<u_int64_t> hash = hasher.gol_board.get_board();
    for (int y = 0; y < size; y++) {
        new_key[y] ^= hash[y] ^ pi[y];
    } 

    for (u_int64_t i : multipliers) {
        for (int y = 0; y < size; y++) {
            new_key[y] ^= std::rotr(seed, (y*i) % size);
            new_key[y] = std::rotl(new_key[y], (seed*i*y) % size);
        }
    }
    
    return CCA_Key(new_key);
}
