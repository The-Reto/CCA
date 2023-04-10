#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <boost/dynamic_bitset.hpp>

enum class Neighbourhood {Moore, vNeumann};

class BitBoard{
    int len, sizex, sizey;
    Neighbourhood neighbourhood;
    boost::dynamic_bitset<> board;
    const int Moore_Neighbours[8];
    const int Moore_Neighbours_EdgeR[8];
    const int Moore_Neighbours_EdgeL[8];
    
    const int xy_to_l(int x, int y) const;
    
    public:
    
    bool get(int index);    
    inline bool get(int x, int y);    
    boost::dynamic_bitset<> get();
    
    void set(const int index, const bool val);    
    void set(const int x, const int y, const bool val);    
    void set(const boost::dynamic_bitset<> &map);
    void set(const boost::dynamic_bitset<unsigned char> &map);
    void reset();
    
    BitBoard(const int sx, const int sy);    
    BitBoard();    
    BitBoard& operator^(const BitBoard& other);
    
    short count_neighbours(const int l);    
    short count_neighbours(const int x, const int y);
    short count_neigbours_moore(const int l);
    short count_neigbours_vNeumann(const int l);
    
    void set_neighbourhood(const Neighbourhood n);
    
    const int get_sizex();
    const int get_sizey();
    
    void visualize();
    
    BitBoard& operator=(const BitBoard& other);
    
};
#endif
