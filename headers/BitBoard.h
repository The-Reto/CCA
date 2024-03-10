#ifndef BIT_BOARD_HEADER
#define BIT_BOARD_HEADER

#include <exception>

template <class type, int size_y> class Bit_Board {

    type board[size_y];

    public:

    Bit_Board() {
        for (int i =  0; i < size_y; i++) {
            board[i] = 0;
        }
    }

    type& operator[](int _y) {
        return board[_y % size_y];
    }

    Bit_Board& operator=(const Bit_Board& other)
    {
        if (this == &other){
            return *this;
        }
        for (int i = 0; i < size_y; i++) {
            board[i] = other.board[i];
        }
        return *this;
    }
};

#endif