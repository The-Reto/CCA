#ifndef BITBOARD_H
#define BITBOARD_H

#include <boost/dynamic_bitset.hpp>

class BitBoard{
    int len, sizex, sizey;
    boost::dynamic_bitset<> board, neighbour_mask, neighbour_mask_edgeR, neighbour_mask_edgeL;
    
    int xy_to_l(int x, int y);
    
    void set_up_moore_neigbours();
    
    public:
    
    bool get(int index);
    
    void set(int index, bool val);
    
    BitBoard(int sx, int sy);
    
    BitBoard();
    
    BitBoard& operator^(const BitBoard& other);
    
    boost::dynamic_bitset<> get();
    
    inline bool get(int x, int y);
    
    void set(boost::dynamic_bitset<> map);
    
    void set(int x, int y, bool val);
    
    int count_neighbours(int l);
    
    int count_neighbours(int x, int y);
    
    int get_sizex();
    int get_sizey();
    
    void visualize();
    
};
#endif
