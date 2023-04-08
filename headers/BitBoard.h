#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <boost/dynamic_bitset.hpp>

enum class Neighbourhood {Moore, vNeumann};

class BitBoard{
    int len, sizex, sizey;
    Neighbourhood neighbourhood;
    boost::dynamic_bitset<> board;
    
    int xy_to_l(int x, int y);
    
    int count_neigbours_moore(const int l);
    int count_neigbours_vNeumann(const int l);
    
    public:
    
    bool get(int index);    
    inline bool get(int x, int y);    
    boost::dynamic_bitset<> get();
    
    void set(int index, bool val);    
    void set(int x, int y, bool val);    
    void set(boost::dynamic_bitset<> map);
    
    BitBoard(int sx, int sy);    
    BitBoard();    
    BitBoard& operator^(const BitBoard& other);
    
    int count_neighbours(const int l);    
    int count_neighbours(const int x, const int y);
    
    void set_neighbourhood(const Neighbourhood n);
    
    int get_sizex();
    int get_sizey();
    
    void visualize();
    
};
#endif
