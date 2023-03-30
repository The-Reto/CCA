#ifndef BITBOARD_CPP
#define BITBOARD_CPP

#include <boost/dynamic_bitset.hpp>

class BitBoard{
    int len, sizex, sizey;
    boost::dynamic_bitset<> board, neighbour_mask, neighbour_mask_edgeR, neighbour_mask_edgeL;
    
    int xy_to_l(int x, int y) {
        while (x < 0) {x += sizex;}
        while (y < 0) {y += sizey;}
        x = x % sizex;
        y = y % sizey;
        return y * sizex + x;
    }
    
    void set_up_moore_neigbours() {
        const static int Moore_len = 8, vNeumann_len = 4;
        const static int Moore_Neighbours[Moore_len] = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
        const static int Moore_Neighbours_EdgeR[Moore_len] = { -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1, sizex+sizey };
        const static int Moore_Neighbours_EdgeL[Moore_len] = { -sizex-sizey, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
        //const static int vNeumann_Neighbours[vNeumann_len] = { -sizex, -1, 1, sizex };
        for (int i = 0; i < Moore_len; i++) {
            int index = Moore_Neighbours[i];
            while (index < 0) {index += len;}
            index = index % len;
            neighbour_mask[index] = true;
            index = Moore_Neighbours_EdgeR[i];
            while (index < 0) {index += len;}
            index = index % len;
            neighbour_mask_edgeR[index] = true;
            index = Moore_Neighbours_EdgeL[i];
            while (index < 0) {index += len;}
            index = index % len;
            neighbour_mask_edgeL[index] = true;
        }
    }
    
    public:
    
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
    
    BitBoard(int sx, int sy): sizex(sx), sizey(sy), len(sx * sy) {    
        board = boost::dynamic_bitset<>(len);
        neighbour_mask = boost::dynamic_bitset<>(len);
        neighbour_mask_edgeR = boost::dynamic_bitset<>(len);
        neighbour_mask_edgeL = boost::dynamic_bitset<>(len);
        
        set_up_moore_neigbours();
    }
    
    BitBoard() : BitBoard(1,1) {}
    
    BitBoard& operator = (const BitBoard& other) {
        board = other.board;
        neighbour_mask = other.neighbour_mask;
        len = other.len;
        sizex = other.sizex;
        sizey = other.sizey;
        return *this;
    }
    
    BitBoard& operator^(const BitBoard& other) {
    	board ^= other.board;
    	return *this;
    }
    
    boost::dynamic_bitset<> get() {
        return board;
    }
    
    inline bool get(int x, int y) {
        return board[ xy_to_l(x,y) ];
    }
    
    void set(boost::dynamic_bitset<> map) {
        for (int i = 0; i<len; i++) {
            set(i, map[i]);
        }
    }
    
    void set(int x, int y, bool val) {
        board[ xy_to_l(x,y) ] = val;
    }
    
    inline int count_neighbours(int l) {
        if (l % sizex == 0) {return (board & ( (neighbour_mask_edgeR << l) | (neighbour_mask_edgeR >> (len - l)) )).count();}
        else if (l % sizex == sizex-1) {return (board & ( (neighbour_mask_edgeL << l) | (neighbour_mask_edgeL >> (len - l)) )).count();}
        else {return (board & ( (neighbour_mask << l) | (neighbour_mask >> (len - l)) )).count();}
    }
    
    inline int count_neighbours(int x, int y) { return count_neighbours(xy_to_l(x,y)); }
    
    const inline int get_sizex() {return sizex;}
    const inline int get_sizey() {return sizey;}
};
#endif
