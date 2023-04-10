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

void GOL::n_step(const int index, boost::dynamic_bitset<>& _board) {
    int neighbours = 0;
    _board.reset();
    for (int i = index; i < len; i += No_Threads) {
        neighbours = board.count_neighbours(i);
        _board.set(i, board.get(i) * survive[neighbours] + (1 -  board.get(i)) * create[neighbours]);
    }
}

void GOL::step() {
    for(int i = 0; i < No_Threads; ++i) {
        threads[i] = std::thread(&GOL::n_step, this, i, std::ref(new_boards[i]));
    }
    for (auto &t : threads) { t.join(); }
    for (const auto &b : new_boards) { new_boards[0] |= b; }
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
