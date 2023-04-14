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
    std::vector<int> Neighbours_EdgeR;
    std::vector<int> Neighbours_EdgeL;
    
    inline const int xy_to_l(const int x, const int y) const {return (sizey-(-y % sizey)) % sizey * sizex + (sizex-(-x % sizex)) % sizex;}
    
    public:
    
    inline bool get(const int index) {return board[(len-(-index % len)) % len];}    
    inline bool get(int x, int y)  {return board[ xy_to_l(x,y) ];}    
    inline boost::dynamic_bitset<unsigned char> get() {return board;}
    
    inline void set(const int index, const bool val) { board[(len-(-index % len)) % len] = val;}
    inline void _set(const int index, const bool val) { board[index] = val;}
    inline void set(const int x, const int y, const bool val)  {board[ xy_to_l(x,y) ] = val;}
    inline void set(const boost::dynamic_bitset<> &map) { for (int i = 0; i<len; i++) { board[i] = map[i]; }}
    inline void set(const boost::dynamic_bitset<unsigned char> &map) {board = map;}
    
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
