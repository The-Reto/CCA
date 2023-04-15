#include <iostream>
#include "../headers/BitBoard.h"

BitBoard::BitBoard(const int sx, const int sy): 
        sizex(sx), 
        sizey(sy), 
        len(sx * sy),  
        board(boost::dynamic_bitset<unsigned char>(len))
    {    
    set_neighbourhood(Neighbourhood::Moore);
}

BitBoard& BitBoard::operator^(const BitBoard& other) {
	board ^= other.board;
	return *this;
}

void BitBoard::count_neighbours(const int l, short& n) {
    if (!(l % sizex))              { n = get(l + Neighbours_EdgeLA)-get(l + Neighbours_EdgeLS); }
    else if (l % sizex == sizex-1) { n = get(l + Neighbours_EdgeRA)-get(l + Neighbours_EdgeRS); }
    else { n = 0; }
    for (int index : Neighbours) {n += get(index+l);}
}

void BitBoard::visualize() {
    std::cout << "\u250f\u2501";
    for (int i = 0; i < sizey-1; i++) { std::cout << "\u2501\u2501"; }
    std::cout << "\u2501\u2513\n";
    for (int i = 0; i < sizex; i++) {
        std::cout << "\u2503";
        for (int j = 0; j < sizey; j++) {
            if (get(i,j)) { std::cout << "\u25A0 "; }
            else { std::cout << "\u25A2 "; }
        }
        std::cout << "\u2503\n";
    }
    std::cout << "\u2517\u2501";
    for (int i = 0; i < sizey-1; i++) { std::cout << "\u2501\u2501"; }
    std::cout << "\u2501\u251b" << std::endl;
}

void BitBoard::set_neighbourhood(const Neighbourhood n) {
    const std::vector<int> vNeumann_Neighbours =        { -sizex, -1, 1, sizex };
    const std::vector<int> vNeumann_Neighbours_EdgeR =  { -sizex, sizex-1, 1, sizex };
    const std::vector<int> vNeumann_Neighbours_EdgeL =  { -sizex, -1, sizex+1, sizex };
    const int vNeumann_Neighbours_EdgeRA = sizex-1, vNeumann_Neighbours_EdgeLA = sizex+1, vNeumann_Neighbours_EdgeRS = -1, vNeumann_Neighbours_EdgeLS = +1;
    const std::vector<int> Moore_Neighbours =           { -sizex-1,   -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const int Moore_Neighbours_EdgeRA = -2*sizex+1, Moore_Neighbours_EdgeLA = 2*sizex-1, Moore_Neighbours_EdgeRS = sizex+1, Moore_Neighbours_EdgeLS = -sizex-1;
    neighbourhood = n;
    switch (neighbourhood) {
        case (Neighbourhood::Moore):
            Neighbours       =  Moore_Neighbours;
            Neighbours_EdgeRA = Moore_Neighbours_EdgeRA;
            Neighbours_EdgeLA = Moore_Neighbours_EdgeLA;
            Neighbours_EdgeRS = Moore_Neighbours_EdgeRS;
            Neighbours_EdgeLS = Moore_Neighbours_EdgeLS;
            break;
        case (Neighbourhood::vNeumann):
            Neighbours       =  vNeumann_Neighbours;
            Neighbours_EdgeRA = vNeumann_Neighbours_EdgeRA;
            Neighbours_EdgeLA = vNeumann_Neighbours_EdgeLA;
            Neighbours_EdgeRS = vNeumann_Neighbours_EdgeRS;
            Neighbours_EdgeLS = vNeumann_Neighbours_EdgeLS;
            break;
    }
}

BitBoard& BitBoard::operator=(const BitBoard& other) {
    if (this == &other) {return *this;}
    sizex = other.sizex;
    sizey = other.sizey;
    board = other.board;
    neighbourhood = other.neighbourhood;
    return *this;
}
