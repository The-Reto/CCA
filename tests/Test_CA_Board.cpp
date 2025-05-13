#include <chrono>
#include "../include/Flexible_CA_Board.h"
#include "../include/CA_Board.h"

int main() {
    const int size = 32;
    
    Flexible_CA_Board<u_int32_t, size> f_gol;
    CA_Board<u_int32_t, size> c_gol;
    Bit_Board<u_int32_t> board;

    for (int i = 0; i < size; i++) {board[i] = 0;}
    // glider
    board[0] = 2;
    board[1] = 4;
    board[2] = 7;
    
    // blinker
    board[10]=3<<3;
    board[11]=3<<3;
    board[12]=3<<5;
    board[13]=3<<5;
    
    // rotator
    board[4] = 7<<24;
   
    // boat
    board[25] = 2<<3;
    board[24] = 40;
    board[23] = 16;
    board[22] = 32;
    
    f_gol.set_board(board);
    const static int generations = 5000000;
    using namespace std::chrono;
    auto start = steady_clock::now();
    for (int i = 0; i < generations; i++) {
        f_gol.step();
    }
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    f_gol.visualize();
    std::cout << "\tFlexible Board: time: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / generations << "ns/generation)\n";

    c_gol.set_board(board);
    using namespace std::chrono;
    start = steady_clock::now();
    for (int i = 0; i < generations; i++) {
        c_gol.step();
    }
    end = steady_clock::now();
    duration = end - start;
    c_gol.visualize();
    std::cout << "\tClassic Board: time: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() / generations << "ns/generation)\n";
}