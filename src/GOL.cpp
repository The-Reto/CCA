#ifndef GOL_CPP
#define GOL_CPP

#include "../headers/GOL.h"

GOL::GOL(const int sx, const int sy, const unsigned int seed) : sizex(sx), sizey(sy), len(sx*sy), board(BitBoard(sizex, sizey)) {
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
        board.set(0,i, s[i]);
    }
    for (auto& bs : new_boards) {bs = boost::dynamic_bitset<>(sizex*sizey);}
}

GOL::GOL(unsigned int seed) : GOL(1,1,seed) {}

GOL::GOL() : GOL(1,1,0) {}

void GOL::set_rules(const bool survive_[9], const bool create_[9]){
    for (int i = 0; i < 9; i++) {
        survive[i] = survive_[i];
        create[i] = create_[i];
    }
}

void GOL::m_step(const int index, int max, boost::dynamic_bitset<>& _board) {
    short neighbours = 0, ind = 0, i;
    _board.reset();
    for (i = index; i < len; i += max) {
        neighbours = board.count_neigbours_moore(i);
        if ((board.get(i) * survive[neighbours]) | (!board.get(i) * create[neighbours])) {_board.set(i, true);}
    }
}

void GOL::o_step(boost::dynamic_bitset<>& _board) {
    short neighbours = 0;
    _board.reset();
    for (int i = 0; i < len; ++i) {
        neighbours = board.count_neigbours_moore(i);
        if ((board.get(i) * survive[neighbours]) | (!board.get(i) * create[neighbours])) {_board.set(i, true);}
    }
}

void GOL::step() {
    if (len > 1024) {
        const int t = 4;
        for(int i = 0; i < t; ++i) {
            threads[i] = std::thread(&GOL::m_step, this, i, t, std::ref(new_boards[i]));
        }
        for (int i = 0; i < t; ++i) { threads[i].join(); new_boards[0] |= new_boards[i]; }
    }
    else {
        o_step(new_boards[0]);
    }
    board.set(new_boards[0]);
}

void GOL::set(const int index, const bool val) {
    board.set(index, val);
}

bool GOL::get(const int index) {
    return board.get(index);
}

void GOL::print() {
    board.visualize();
}

BitBoard GOL::get_board() {
    return board;
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
