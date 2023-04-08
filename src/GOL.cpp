#ifndef GOL_CPP
#define GOL_CPP

#include "../headers/GOL.h"

GOL::GOL(int sx, int sy, unsigned int seed) : sizex(sx), sizey(sy) {
    std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
    board = BitBoard(sizex, sizey);
    b_board = BitBoard(sizex, sizey);
    for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
        board.set(5,i+3, s[i]);
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

void GOL::n_step(int index, int max) {
    int neighbours = 0, val = 0;
    std::unique_lock<std::mutex> guard(m, std::defer_lock);
    for (int i = index; i < sizex*sizey; i+=max) {
        neighbours = board.count_neighbours(i);
        val = board.get(i) * survive[neighbours] + (1 -  board.get(i)) * create[neighbours];
        guard.lock();
        b_board.set(i, val);
        guard.unlock();
    }
}

void GOL::step() {
    const static int No_Threads = 4;
    std::vector<std::thread> threads;
    for(int i = 0; i < No_Threads; i++) {
        threads.push_back(std::thread(&GOL::n_step, this, i, No_Threads));
    }
    for(auto &t : threads) {
        t.join();
    }
    board = b_board;
}

void GOL::steps(int steps){
    for (int i = 0; i < steps; i++) { step(); }
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
    b_board = other.b_board;
    set_rules(other.survive, other.create);
    return *this;
}
#endif
