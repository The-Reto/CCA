#include <iostream>
#include "../headers/BitBoard.h"

int BitBoard::xy_to_l(int x, int y) {
    if (x < 0) {x = -(-x % sizex) + sizex;}
    if (y < 0) {y = -(-y % sizey) + sizey;}
    x = x % sizex;
    y = y % sizey;
    return y * sizex + x;
}

bool BitBoard::get(int index) {
    if (index < 0) {index = -(-index % len) + len;}
    index = index % len;
    return board[index];
}

void BitBoard::set(int index, const bool val) {
    if (index < 0) {index = -(-index % len) + len;}
    index = index % len;
    board[index] = val;
}

BitBoard::BitBoard(const int sx, const int sy): sizex(sx), sizey(sy), len(sx * sy) {    
    board = boost::dynamic_bitset<>(len);
    neighbourhood = Neighbourhood::Moore;
}

BitBoard::BitBoard() : BitBoard(1,1) {}

BitBoard& BitBoard::operator^(const BitBoard& other) {
	board ^= other.board;
	return *this;
}

boost::dynamic_bitset<> BitBoard::get() {
    return board;
}

inline bool BitBoard::get(const int x, const int y) {
    return board[ xy_to_l(x,y) ];
}

void BitBoard::set(boost::dynamic_bitset<> map) {
    for (int i = 0; i<len; i++) {
        set(i, map[i]);
    }
}

void BitBoard::set(const int x, const int y, const bool val) {
    board[ xy_to_l(x,y) ] = val;
}

int BitBoard::count_neighbours(const int l) {
    if (neighbourhood == Neighbourhood::Moore) {return count_neigbours_moore(l);}
    else if (neighbourhood == Neighbourhood::vNeumann) {return count_neigbours_vNeumann(l);}
    else {return -1;}
}

inline int BitBoard::count_neighbours(const int x, const int y) { return count_neighbours(xy_to_l(x,y)); }

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

int BitBoard::count_neigbours_moore(const int l){
    const std::vector<int> Moore_Neighbours = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const std::vector<int> Moore_Neighbours_EdgeR = { -2*sizex+1, -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex };
    const std::vector<int> Moore_Neighbours_EdgeL = { -sizex+1, -1,1, sizex-1, sizex, sizex+1, 2*sizex-1, -sizex };
    int n = 0;
    if (l % sizex == 0) {
        for (int index : Moore_Neighbours_EdgeL) {n += get(index+l);}
    }
    else if (l % sizex == sizex-1) {
        for (int index : Moore_Neighbours_EdgeR) { n += get(index+l);}
    }
    else {
        for (int index : Moore_Neighbours) { n += get(index+l);}
    }
    return n;
}

int BitBoard::count_neigbours_vNeumann(const int l){
    const std::vector<int> vNeumann_Neighbours = { -sizex, -1, 1, sizex };
    const std::vector<int> vNeumann_Neighbours_EdgeR = { -sizex, sizex-1, 1, sizex };
    const std::vector<int> vNeumann_Neighbours_EdgeL = { -sizex, -1, sizex+1, sizex };
    int n = 0;
    if (l % sizex == 0) {
        for (int index : vNeumann_Neighbours_EdgeR) {n += get(index+l);}
    }
    else if (l % sizex == sizex-1) {
        for (int index : vNeumann_Neighbours_EdgeL) { n += get(index+l);}
    }
    else {
        for (int index : vNeumann_Neighbours) { n += get(index+l);}
    }
    return n;
}

void BitBoard::set_neighbourhood(const Neighbourhood n) {
    neighbourhood = n;
}
