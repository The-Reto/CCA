#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <boost/dynamic_bitset.hpp>

enum class Neighbourhood {Moore, vNeumann};

class BitBoard{
    int len, sizex, sizey;
    Neighbourhood neighbourhood;
    boost::dynamic_bitset<> board;
    
    const int xy_to_l(int x, int y) const;
    
    int count_neigbours_moore(const int l);
    int count_neigbours_vNeumann(const int l);
    
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
    
    int count_neighbours(const int l);    
    int count_neighbours(const int x, const int y);
    
    void set_neighbourhood(const Neighbourhood n);
    
    const int get_sizex();
    const int get_sizey();
    
    void visualize();
    
};
#endif
