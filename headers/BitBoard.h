#ifndef BIT_BOARD_HEADER
#define BIT_BOARD_HEADER

#include <exception>
#include <iostream>

template <class type> class Bit_Board {

    const static int size = sizeof(type) * 8;
    type board[size];

    public:

    Bit_Board() {
        for (int i =  0; i < size; i++) {
            board[i] = 0;
        }
    }

    type& operator[](int _y) {
        return board[_y % size];
    }

    Bit_Board& operator=(const Bit_Board& other)
    {
        if (this == &other){
            return *this;
        }
        for (int i = 0; i < size; i++) {
            board[i] = other.board[i];
        }
        return *this;
    }

    /// @brief returns the bit at position x/y as a boolean
    /// @param x x position to be returned
    /// @param y y position to be returned
    /// @param layer what layer to return: 0 (default) -> GOL Board, 1 -> LSB Board, 2 -> MSB Board
    /// @return Bit at position x/y as a boolean
    inline bool get(int x, int y) {
        return (board[y%size] >> (x%sizeof(type) * 8)) & 1;
    }

    /// @brief sets the bit at position x/y as a boolean
    /// @param x x position to be set
    /// @param y y position to be set
    /// @param value (bool) the new value of the bit at position x/y
    inline void set(int x, int y, bool value) {
        board[y%size] = board[y%size] | ((value) << (x%size));
    }

    /// @brief Visualizes the BitBoard on the console
    const static void visualize(Bit_Board<type> _board)  {
        std::cout << "\u250f\u2501";
        for (int i = 0; i < Bit_Board<type>::size; i++) { std::cout << "\u2501\u2501"; }
        std::cout << "\u2513\n";
        for (int i = 0; i < Bit_Board<type>::size; i++) {
            std::cout << "\u2503 ";
            for (int j = 0; j < Bit_Board<type>::size; j++) {
                if (_board.get(j,i)) { std::cout << "\u25A0 "; }
                else { std::cout << "\u25A2 "; }
            }
            std::cout << "\u2503\n";
        }
        std::cout << "\u2517\u2501";
        for (int i = 0; i < Bit_Board<type>::size; i++) { std::cout << "\u2501\u2501"; }
        std::cout << "\u251b" << std::endl;
    }
};

#endif