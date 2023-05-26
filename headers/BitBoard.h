#ifndef BITBOARD_H
#define BITBOARD_H

#include <iostream>
#include <boost/dynamic_bitset.hpp>

enum class Neighbourhood {Moore, vNeumann};

class BitBoard{
    int len, sizex, sizey;
    Neighbourhood neighbourhood;
    boost::dynamic_bitset<unsigned char> board;
    std::vector<int> Neighbours;
    int Neighbours_EdgeRA, Neighbours_EdgeLA, Neighbours_EdgeRS, Neighbours_EdgeLS;
    
    inline const int xy_to_l(const int x, const int y) const {return ((y % sizey + sizey) % sizey) * sizex + (x % sizex + sizex) % sizex;}
    
    public:
    
    inline bool get(const int index) {return board[(index % len + len) % len];}    
    inline bool get(int x, int y)  {return board[ xy_to_l(x,y) ];}    
    inline boost::dynamic_bitset<unsigned char> get() {return board;}
    
    inline void set(const int index, const bool val) { board[(index % len + len) % len] = val;}
    inline void _set(const int index, const bool val) { board[index] = val;}
    inline void set(const int x, const int y, const bool val)  {board[ xy_to_l(x,y) ] = val;}
    void set(const boost::dynamic_bitset<unsigned char> &map);
    
    inline void reset() { board.reset();}
    
    BitBoard(const int sx, const int sy);    
    inline BitBoard() : BitBoard(1,1) {}
    
    void count_neighbours(const int l, short& n);    
    inline void count_neighbours(const int x, const int y, short& n) {count_neighbours(xy_to_l(x,y), n); }
    
    void set_neighbourhood(const Neighbourhood n);
    
    const inline int get_sizex() {return sizex;}
    const inline int get_sizey() {return sizey;}

    void visualize();
    
    BitBoard& operator=(const BitBoard& other);
    BitBoard& operator^(const BitBoard& other);
    
};
#endif
