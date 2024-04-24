#include "../../headers/Neighbour_Counting_Board.h"

class Cycle_Length_Board: public Neighbour_Counting_Board<u_int8_t> {
    const static int size = 8;
    constexpr static u_int8_t pi[8] = {
        0b11011011,
        0b01101101,
        0b11111011,
        0b10111010,
        0b10110101,
        0b01101000,
        0b11101111,
        0b11110110
    };

    public:
    Cycle_Length_Board() {
        for (int y = 0; y < size; y++) {
            board[0][y] = pi[y];
        }
    }

    void update_GOL_board() {
        u_int64_t lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
        for (int i = 0; i < size; i++) {
            m = board[0][i];
            lsb_o = board[1][(i+size-1)%size];  msb_o = board[2][(i+size-1)%size];
            lsb_c = (~m&board[1][i])|(m&(board[2][i]&~board[1][i]));
            msb_c = (board[2][i]&board[1][i])|(board[2][i]&~m);
            lsb_u = board[1][(i+1)%size];       msb_u = board[2][(i+1)%size];
            board[0][i] = board[1][(i+2)%size] ^ (pi[i] & board[2][(i+size-2)%size]) ^ (
            ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours (happens independently of m) : two msb set, 1 lsb OR
            ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 5 neigbours : 1 msb, 3 lsb
            ~m & // create new life where current board is empty IF:
            (
                ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
                (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
                ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
                (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) // 4 neigbours : 2 msb set, no lsb set
            ) | m & // survive where current board is full IF:
            (
                ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
                ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) // 3 neigbours : all lsb set, all msb unset
            ));
        }
    }

    void step() {
        update_msb_lsb();
        update_GOL_board();
    }

    void steps(u_int64_t steps) {
        for (int i = 0; i< steps; i++) {step();}
}
};

bool check(Bit_Board<u_int8_t> test, Bit_Board<u_int8_t> original, int y_shift, int x_shift) {
    for (int i = 0; i < 8; i++) {
        if (test[i+y_shift] != std::rotl(original[i], x_shift)) {
            return false;
        }
    }
    return true;
}

int main() {
    const static int max_cycle = 5'000;
    Cycle_Length_Board test;
    Bit_Board<u_int8_t> prev[max_cycle], curr[max_cycle];

    bool go = true, part = true;
    u_int64_t steps = 450'000'000, b_steps=0;
    u_int64_t cycle_len;
    for (int i = 0; i < steps; i++) {
        test.step();
    }
    while (go) {
        for (int i = 0; i < max_cycle; i++) {
            curr[steps%(max_cycle)] = test.get_board();
            if (steps % 1'000'000 == 0) {std::cout << steps / 1'000'000.0  << " , " << b_steps << std::endl;}
            steps++;
            test.step();
        }
        prev[b_steps%max_cycle] = test.get_board();
        b_steps++;
        test.step();
        steps++;
        for (int i = 0; i < max_cycle; i++) {
            for (int j = 0; j < max_cycle; j++) {
                if (curr[i] == prev[j]) {
                    go = false;
                    break;
                }
            }
        }
    }
    std::cout << "After " << steps << " / " << INT64_MAX << " steps the pattern reaches a cycle" << std::endl;
    std::cout << ((double) 100.0)*steps / INT64_MAX << " percent of max" << std::endl;
    u_int64_t cycle = 1;
    Bit_Board<u_int8_t> start = test.get_board();
    test.step();
    while (start != test.get_board())
    {
        cycle++;
        test.step();
    }
    std::cout << "Cycle Length: " << cycle << " reached after " << steps << " steps." << std::endl;

    return 0;
}