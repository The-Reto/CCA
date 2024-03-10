#include "../headers/GOL_Keygen.h"
#include "../headers/Flexible_GOL_Board.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Keygen test("a");
    // Flexible_GOL_Board<u_int64_t, 64> run_board;
    // u_int64_t board[64];
    // for (int i = 0; i < 64; i++) {
    // board[i] = test.gol_board.board[0][i];
    // }
    // run_board.set_board(board);
    // bool create[9] =  {0,0,1,0,1,1,0,0,0};
    // bool survive[9] = {0,0,0,1,1,1,0,0,0};
    // run_board.set_survive(survive);
    // run_board.set_create(create);
    // for (long i = 0; i < 128; i++) {
    //     run_board.step();
    // }
    // int res = 0;
    // while (true) {
    //     res = write(1,&run_board.get_board()[0],512);
    //     run_board.step();
    // }
    for (long i = 0; i < 10; i++) {
    std::cout << test.get_streched_key(32).to_ulong() << std::endl;
    }
}
