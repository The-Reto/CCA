#ifndef GOL_CPP
#define GOL_CPP

#include "../headers/GOL.h"

GOL::GOL(const int sx, const int sy, const unsigned int seed) : sizex(sx), sizey(sy), len(sx*sy), board(BitBoard(sizex, sizey)), multi_thread(len > 1024) {
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
        board.set(0,i, s[i]);
    }
    for (auto& bs : new_boards) {bs = boost::dynamic_bitset<unsigned char>(len);}
}

void GOL::set_rules(const bool survive_[9], const bool create_[9]){
    for (int i = 0; i < 9; i++) {
        survive[i] = survive_[i];
        create[i] = create_[i];
    }
}

void GOL::m_step(const int index, const int max, boost::dynamic_bitset<unsigned char>& _board) {
    short neighbours = 0;
    for (int i = index; i < len; i += max) {
        board.count_neighbours(i, neighbours);
        _board.set(i, (board.get(i) * survive[neighbours]) | (!board.get(i) * create[neighbours]));
    }
}

void GOL::step() {
    if (multi_thread) {
        new_boards[0].reset();
        for(int i = 0; i < 4; ++i) {
            threads[i] = std::thread(&GOL::m_step, this, i, 4, std::ref(new_boards[i]));
        }
        for (int i = 0; i < 4; ++i) { threads[i].join(); new_boards[0] |= new_boards[i]; }
    }
    else {
        m_step(0,1,new_boards[0]);
    }
    board.set(new_boards[0]);
}

GOL& GOL::operator=(const GOL& other) {
    // Guard self assignment
    if (this == &other)
        return *this;
    sizex = other.sizex;
    sizey = other.sizey;
    board = other.board;
    set_rules(other.survive, other.create);
    return *this;
}
#endif
