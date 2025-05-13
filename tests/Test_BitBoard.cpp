#include "../include/BitBoard.h"
#include <iostream>

int main()
{
    Bit_Board<u_int16_t> board_a;
    Bit_Board<u_int16_t> board_b;

    board_a[3] = 345;

    for (int i = 0; i < 20; i++) {
        std::cout << board_a[i] << ", ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << board_b[i] << ", ";
    }
    std::cout << std::endl;
    board_b = board_a;
    for (int i = 0; i < 16; i++) {
        std::cout << board_b[i] << ", ";
    }
    std::cout << std::endl;
}
