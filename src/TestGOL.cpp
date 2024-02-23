#include <bit>
#include <iostream>
#include <chrono>


#define TYPE u_int64_t
const static int size = 64;

TYPE board[size][3];

inline bool get(int x, int y, int layer = 0) {
    return (board[y][layer] >> x) & 1;
}

void update_msb_lsb() {
    for (int i = 0; i < size; i++) {
        TYPE l = std::rotl(board[i][0], 1), r = std::rotr(board[i][0], 1), c = board[i][0];
        board[i][1] = (c ^ l) ^ r; // LSB
        board[i][2] = (c & l) | (c & r) | (r & l);//MSB
    }
}

const inline TYPE exactly1of3(TYPE a, TYPE b, TYPE c) {
    return ( a & ~b & ~c | ~a & b & ~c | ~a & ~b & c);
}

const inline TYPE exactly2of3(TYPE a, TYPE b, TYPE c) {
    return ( a & b & ~c | ~a & b & c | a & ~b & c);
}

const inline TYPE noneof3(TYPE a, TYPE b, TYPE c) {
    return ~(a | b | c) ;
}

const inline TYPE all3(TYPE a, TYPE b, TYPE c) {
    return ( a & b & c );
}

void step() {
    static TYPE lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
    bool survive[9] = {0,0,1,1,0,0,0,0,0}, create[9] =  {0,0,0,1,0,0,0,0,0};
    update_msb_lsb();
    for (int i = 0; i < size; i++) {
        lsb_o = board[(i+size-1)%size][1];  msb_o = board[(i+8-1)%8][2];
        lsb_c = board[i][1];        msb_c = board[i][2];
        lsb_u = board[(i+1)%size][1];  msb_u = board[(i+1)%8][2];
        m = board[i][0];
        board[i][0] = ~m & // create new life
        ( 
            create[0] * (noneof3(msb_o, msb_c, msb_u) & noneof3(lsb_c, lsb_o, lsb_u)) ^ // 0 neigbours : nothing set
            create[1] * ( noneof3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c) ) ^ // 1 neigbour : 0 msb set, 1 lsb set
            create[2] * ( (noneof3(lsb_o, lsb_u, lsb_c) & exactly1of3(msb_o, msb_u, msb_c)) ^ // 2 neigbors : 1 msb set, 0 lsb set OR
             (noneof3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c) ) ) ^ // 2 neigbours : 2 lsb set, 0 msb set
            create[3] * ( ( exactly1of3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c) ) ^ // 3 neigbours : 1 lsb set, 1 msb set OR
             ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) ^ // 3 neigbours : all lsb set, all msb unset
            create[4] * ( (exactly1of3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c)) ^ // 4 neigbours : 1 msb set, 2 lsb set OR
             (exactly2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) ^ // 4 neigbours : 2 msb set, no lsb set
            create[5] * ( (exactly2of3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c)) ^ // 5 neigbours : two msb set, 1 lsb OR
            ( exactly1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) ^ // 5 neigbours : 1 msb, 3 lsb
            create[6] * ( (all3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ^ // 6 neigbours : 3 msb, no lsb
            ( exactly2of3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c) )) ^ // 6 neigbours : 2 msb, 2 lsb
            create[7] * ( (all3(msb_o, msb_u, msb_c) & exactly1of3(lsb_o, lsb_u, lsb_c) ) ^ // 7 neigbours : 3 msb, 1 lsb
             (exactly2of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) ^// 7 neigbours : 2 msb, 3 lsb 
            create[8] * (all3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c))   // 8 neigbours : 3 msb, 2 lsb
        );
        t = msb_c & lsb_c;
        lsb_c = msb_c & ~lsb_c;
        msb_c = t;
        board[i][0] |= m & // survive
        (
            survive[0] * (noneof3(msb_o, msb_c, msb_u) & noneof3(lsb_c, lsb_o, lsb_u)) ^ // 0 neigbours : nothing set
            survive[1] * ( noneof3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c) ) ^ // 1 neigbour : 0 msb set, 1 lsb set
            survive[2] * ( (noneof3(lsb_o, lsb_u, lsb_c) & exactly1of3(msb_o, msb_u, msb_c)) ^ // 2 neigbors : 1 msb set, 0 lsb set OR
             (noneof3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c) ) ) ^ // 2 neigbours : 2 lsb set, 0 msb set
            survive[3] * ( ( exactly1of3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c) ) ^ // 3 neigbours : 1 lsb set, 1 msb set OR
             ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) ^ // 3 neigbours : all lsb set, all msb unset
            survive[4] * ( (exactly1of3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c)) ^ // 4 neigbours : 1 msb set, 2 lsb set OR
             (exactly2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) ^ // 4 neigbours : 2 msb set, no lsb set
            survive[5] * ( (exactly2of3(msb_o, msb_u, msb_c) & exactly1of3(lsb_u, lsb_o, lsb_c)) ^ // 5 neigbours : two msb set, 1 lsb OR
            ( exactly1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) ^ // 5 neigbours : 1 msb, 3 lsb
            survive[6] * ( (all3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ^ // 6 neigbours : 3 msb, no lsb
            ( exactly2of3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c) )) ^ // 6 neigbours : 2 msb, 2 lsb
            survive[7] * ( (all3(msb_o, msb_u, msb_c) & exactly1of3(lsb_o, lsb_u, lsb_c) ) ^ // 7 neigbours : 3 msb, 1 lsb
             (exactly2of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) ^// 7 neigbours : 2 msb, 3 lsb 
            survive[8] * (all3(msb_o, msb_u, msb_c) & exactly2of3(lsb_o, lsb_u, lsb_c))   // 8 neigbours : 3 msb, 2 lsb
        );
    }
}

void visualize() {
    update_msb_lsb();
    std::cout << "\u250f\u2501";
    for (int i = 0; i < size; i++) { std::cout << "\u2501\u2501"; }
    std::cout << "\u2513\n";
    for (int i = 0; i < size; i++) {
        std::cout << "\u2503 ";
        for (int j = 0; j < size; j++) {
            if (get(j,i)) { std::cout << "\u25A0 "; }
            else { std::cout << "\u25A2 "; }
        }
        std::cout << "\u2503\n";
    }
    std::cout << "\u2517\u2501";
    for (int i = 0; i < size; i++) { std::cout << "\u2501\u2501"; }
    std::cout << "\u251b" << std::endl;
}

int main() {
    for (int i = 0; i < size; i++) {board[i][0] = 0;}
    // glider
    
    board[0][0] = 2;
    board[1][0] = 4;
    board[2][0] = 7;
    
    // blinker
    /*
    board[0][0]=3;
    board[1][0]=3;
    board[2][0]=3<<2;
    board[3][0]=3<<2;
    */
    // rotator
    /*
    board[4][0] = 7<<3;
    */

   /*
    board[5][0] = 2<<3;
    board[4][0] = 40;
    board[3][0] = 16;
    board[2][0] = 32;
   */
    const static int generations = 10000;
    using namespace std::chrono;
    visualize();
    auto start = steady_clock::now();
    for (int i = 0; i < generations; i++) {
        step();
    }
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    visualize();
    std::cout << "\ttime: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / generations << "ms/generation)\n";
}