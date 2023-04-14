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
    n = 0;
    if (l % sizex == 0) {
        for (int index : Neighbours_EdgeL) {n += get(index+l);}
    }
    else if (l % sizex == sizex-1) {
        for (int index : Neighbours_EdgeR) {n += get(index+l);}
    }
    else {
        for (int index : Neighbours) {n += get(index+l);}
    }
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
    const std::vector<int> Moore_Neighbours =           { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const std::vector<int> Moore_Neighbours_EdgeR =     { -2*sizex+1, -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex };
    const std::vector<int> Moore_Neighbours_EdgeL =     { -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1, 2*sizex-1 };
    neighbourhood = n;
    switch (neighbourhood) {
        case (Neighbourhood::Moore):
            Neighbours       =  Moore_Neighbours;
            Neighbours_EdgeR =  Moore_Neighbours_EdgeR;
            Neighbours_EdgeL =  Moore_Neighbours_EdgeL;
            break;
        case (Neighbourhood::vNeumann):
            Neighbours       =  vNeumann_Neighbours;
            Neighbours_EdgeR =  vNeumann_Neighbours_EdgeR;
            Neighbours_EdgeL =  vNeumann_Neighbours_EdgeL;
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
