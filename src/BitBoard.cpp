#include <iostream>
#include "../headers/BitBoard.h"

int BitBoard::xy_to_l(int x, int y) {
    while (x < 0) {x += sizex;}
    while (y < 0) {y += sizey;}
    x = x % sizex;
    y = y % sizey;
    return y * sizex + x;
}

bool BitBoard::get(int index) {
    while (index < 0) {index += len;}
    index = index % len;
    return board[index];
}

void BitBoard::set(int index, bool val) {
    while (index < 0) {index += len;}
    index = index % len;
    board[index] = val;
}

BitBoard::BitBoard(int sx, int sy): sizex(sx), sizey(sy), len(sx * sy) {    
    board = boost::dynamic_bitset<>(len);
}

BitBoard::BitBoard() : BitBoard(1,1) {}

BitBoard& BitBoard::operator^(const BitBoard& other) {
	board ^= other.board;
	return *this;
}

boost::dynamic_bitset<> BitBoard::get() {
    return board;
}

inline bool BitBoard::get(int x, int y) {
    return board[ xy_to_l(x,y) ];
}

void BitBoard::set(boost::dynamic_bitset<> map) {
    for (int i = 0; i<len; i++) {
        set(i, map[i]);
    }
}

void BitBoard::set(int x, int y, bool val) {
    board[ xy_to_l(x,y) ] = val;
}

int BitBoard::count_neighbours(int l) {
    const std::vector<int> Moore_Neighbours = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const std::vector<int> Moore_Neighbours_EdgeR = { -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1, sizex+sizey };
    const std::vector<int> Moore_Neighbours_EdgeL = { -sizex-sizey, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    int n = 0;
    if (l % sizex == 0) {
        for (int index : Moore_Neighbours_EdgeR) {n += get(index+l);}
    }
    else if (l % sizex == sizex-1) {
        for (int index : Moore_Neighbours_EdgeL) { n += get(index+l);}
    }
    else {
        for (int index : Moore_Neighbours) { n += get(index+l);}
    }
    return n;
}

inline int BitBoard::count_neighbours(int x, int y) { return count_neighbours(xy_to_l(x,y)); }

inline int BitBoard::get_sizex() {return sizex;}
inline int BitBoard::get_sizey() {return sizey;}

void BitBoard::visualize() {
    std::cout << "\u250f\u2501";
    for (int i = 0; i < sizey; i++) {
        std::cout << "\u2501\u2501";
    }
    std::cout << "\u2501\u2513\n";
    for (int i = 0; i < sizex; i++) {
        std::cout << "\u2503 ";
        for (int j = 0; j < sizey; j++) {
            if (get(i,j)) {
                std::cout << "\u25A0 ";
            }
            else {
                std::cout << "\u25A2 ";
            }
        }
        std::cout << " \u2503\n";
    }
    std::cout << "\u2517\u2501";
    for (int i = 0; i < sizey; i++) {
        std::cout << "\u2501\u2501";
    }
    std::cout << "\u2501\u251b" << std::endl;
}
