#ifndef GOL_CPP
#define GOL_CPP

#include "../headers/GOL.h"

GOL::GOL(const int sx, const int sy, const unsigned int seed) : sizex(sx), sizey(sy), board_index(0), boards({BitBoard(sizex, sizey), BitBoard(sizex, sizey)}) {
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
        boards[board_index].set(0,i, s[i]);
    }
}

GOL::GOL(unsigned int seed) : GOL(1,1,seed) {}

GOL::GOL() : GOL(1,1,0) {}

void GOL::set_rules(const bool survive_[9], const bool create_[9]){
    for (int i = 0; i < 9; i++) {
        survive[i] = survive_[i];
        create[i] = create_[i];
    }
}

void GOL::n_step(const int index, const int max) {
    int neighbours = 0, val = 0;
    std::unique_lock<std::mutex> guard(m, std::defer_lock);
    for (int i = index; i < sizex*sizey; i += max) {
        neighbours = boards[board_index].count_neighbours(i);
        val = boards[board_index].get(i) * survive[neighbours] + (1 -  boards[board_index].get(i)) * create[neighbours];
        guard.lock();
        boards[(board_index + 1) % 2].set(i, val);
        guard.unlock();
    }
}

void GOL::step() {
    const static int No_Threads = 4;
    std::array<std::thread, No_Threads> threads;
    for(int i = 0; i < No_Threads; ++i) {
        threads[i] = std::thread(&GOL::n_step, this, i, No_Threads);
    }
    for(auto &t : threads) { t.join(); }
    board_index = (board_index + 1) % 2;
}

void GOL::steps(int steps){
    for (int i = 0; i < steps; i++) { step(); }
}

void GOL::print() {
    boards[board_index].visualize();
}

BitBoard GOL::get_board() {
    return boards[board_index];
}

GOL& GOL::operator=(const GOL& other) {
    // Guard self assignment
    if (this == &other)
        return *this;
    sizex = other.sizex;
    sizey = other.sizey;
    boards = other.boards;
    set_rules(other.survive, other.create);
    return *this;
}
#endif
