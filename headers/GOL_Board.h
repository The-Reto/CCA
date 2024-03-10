#ifndef GOL_BOARD_HEADER
#define GOL_BOARD_HEADER

#include <bit>
#include <iostream>
#include <array>
#include "../headers/BitBoard.h"

template <class TYPE, int size> class GOL_Board {
    public:
    /// @brief returns true where exactly 1 of the three inputs is true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where exactly one of the three inputs was true
    const static inline TYPE any1of3(TYPE a, TYPE b, TYPE c) {
        return a & ~b & ~c | ~a & b & ~c | ~a & ~b & c;
    }

    /// @brief returns true where exactly 2 of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where exactly two of the three inputs were true
    const static inline TYPE any2of3(TYPE a, TYPE b, TYPE c) {
        return a & b & ~c | ~a & b & c | a & ~b & c;
    }

    /// @brief returns true where none of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where none of the three inputs were true
    const static inline TYPE noneof3(TYPE a, TYPE b, TYPE c) {
        return ~a&~b&~c ;
    }

    /// @brief returns true where all three of the three inputs are true
    /// @param a u_intX_t to be compared
    /// @param b u_intX_t to be compared
    /// @param c u_intX_t to be compared
    /// @return a u_intX_t that is true where all of the three inputs were true
    const static inline TYPE all3(TYPE a, TYPE b, TYPE c) {
        return a & b & c;
    }

    //TYPE board[3][size];
    Bit_Board<TYPE> board[3];

    /// @brief Sets the GOL-Board to a predefined state
    /// @param _board a GOL-Board used to set the internal GOL-Board
    void set_board(Bit_Board<TYPE> _board) {
        board[0] = _board;
    }

    /// @brief Sets the GOL-Board to a predefined state
    /// @param _board a GOL-Board used to set the internal GOL-Board
    Bit_Board<TYPE>& get_board(int layer = 0) {
        return board[layer];
    }

    /// @brief returns the bit at position x/y as a boolean
    /// @param x x position to be returned
    /// @param y y position to be returned
    /// @param layer what layer to return: 0 (default) -> GOL Board, 1 -> LSB Board, 2 -> MSB Board
    /// @return Bit at position x/y as a boolean
    inline bool get(int x, int y, short layer = 0) {
        return board[layer].get(x,y);
    }

    /// @brief returns the bit at position index as a boolean, where row-major indexing is used
    /// @param index (int) position of the bit to be returned
    /// @return Bit at position index as a boolean
    inline bool get(int index, short layer = 0) {
        return get(index % size, index / size, layer);
    }

    /// @brief sets the bit at position x/y as a boolean
    /// @param x x position to be set
    /// @param y y position to be set
    /// @param value (bool) the new value of the bit at position x/y
    inline void set(int x, int y, bool value, short layer = 0) {
        board[layer].set(x,y,value);
    }

    /// @brief sets the bit at position index as a boolean
    /// @param index (int) position of the bit to be returned
    /// @param value (bool) the new value of the bit at position index
    inline void set(int index, bool value) {
        set(index % size, index / size, value);
    }

    /// @brief Upbades the LSB- and MSB-Boards based on the GOL Board, needs to be run before updating GOL-Board
    void update_msb_lsb() {
        TYPE l, r, c;
        for (int i = 0; i < size; i++) {
            l = std::rotl(board[0][i], 1), r = std::rotr(board[0][i], 1), c = board[0][i];
            board[1][i] = (c ^ l) ^ r; // LSB
            board[2][i] = (c & l) | (c & r) | (r & l);//MSB
        }
    }

    void visualize() {
        Bit_Board<TYPE>::visualize(board[0]);
    }
};

#endif