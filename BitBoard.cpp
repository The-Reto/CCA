#ifndef BITBOARD_CPP
#define BITBOARD_CPP

#include <bitset>

template <int sizex, int sizey> class BitBoard{
    int len;
    std::bitset< sizex * sizey > board, neighbour_mask;
    const static int Moore_len = 8, vNeumann_len = 4;
    const int Moore_Neighbours[Moore_len] = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const int vNeumann_Neighbours[vNeumann_len] = { -sizex, -1, 1, sizex };

    
    int xy_to_l(int x, int y) {
        while (x < 0) {x += sizex;}
        while (y < 0) {y += sizey;}
        x = x % sizex;
        y = y % sizey;
        return y * sizex + x;
    }
    
    bool get(int index) {
        while (index < 0) {index += len;}
        index = index % len;
        return board[index];
    }
    
    void set(int index, bool val) {
        while (index < 0) {index += len;}
        index = index % len;
        board[index] = val;
    }
    
    public:
    BitBoard() {
        len = sizex * sizey;
        for (int i = 0; i < Moore_len; i++) {
            int index = Moore_Neighbours[i];
		    while (index < 0) {index += len;}
		    index = index % len;
            neighbour_mask[index] = true;
        }
    }
    
    BitBoard& operator = (const BitBoard& other) {
        board = other.board;
        neighbour_mask = other.neighbour_mask;
        return *this;
    }
    
    std::bitset<sizex*sizey> get() {
        return board;
    }
    
    inline bool get(int x, int y) {
        return board[ xy_to_l(x,y) ];
    }
    
    void set(std::bitset<sizex*sizey> map) {
        for (int i = 0; i<len; i++) {
            set(i, map[i]);
        }
    }
    
    void set(int x, int y, bool val) {
        board[ xy_to_l(x,y) ] = val;
    }
    
    inline int count_neighbours(int l) {
        return (board & ( (neighbour_mask << l) | (neighbour_mask >> (len - l)) )).count();
    }
    
    inline int count_neighbours(int x, int y) { return count_neighbours(xy_to_l(x,y)); }
    
    const inline int get_sizex() {return sizex;}
    const inline int get_sizey() {return sizey;}
};
#endif
