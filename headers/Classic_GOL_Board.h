#include "./GOL_Board.h"

/// @brief A GOL-Board with classic rules - faster than a class where the rules are flexible
/// @tparam TYPE u_intX_t used to store the bord, simultaneously sets width of GOL-Board (eg. u_int32_t, sets the width to 32)
/// @tparam size height of the GOL-Board
template <class TYPE, int size> class Classic_GOL_Board: public Neighbour_Counting_Board<TYPE> {
    using Neighbour_Counting_Board<TYPE>::update_msb_lsb;
    using Neighbour_Counting_Board<TYPE>::board;
    using Neighbour_Counting_Board<TYPE>::noneof3;
    using Neighbour_Counting_Board<TYPE>::any1of3;
    using Neighbour_Counting_Board<TYPE>::any2of3;
    using Neighbour_Counting_Board<TYPE>::all3;

    public:

    /// @brief Default constructor
    Classic_GOL_Board() {
    }

    void steps(int number) {
        for (int i = 0; i < number; i++) {step();}
    }

    /// @brief Does one GOL-Update step
    void step()  {
        update_msb_lsb();
        update_GOL_board();
    }

    /// @brief updates the GOL-Board based on the LSB- and MSB-board
    void update_GOL_board() {
        TYPE lsb_o, lsb_c, lsb_u, msb_o, msb_c, msb_u, m, t;
        for (int i = 0; i < size; i++) {
            lsb_o = board[1][(i+size-1)%size];  msb_o = board[2][(i+size-1)%size];
            lsb_c = board[1][i];                msb_c = board[2][i];
            lsb_u = board[1][(i+1)%size];       msb_u = board[2][(i+1)%size];
            m = board[0][i];
            board[0][i] = ~m & // create new life where current board is empty IF:
            ( 
                ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) |   // 3 neigbours : 1 lsb set, 1 msb set OR
                ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c))         // 3 neigbours : all lsb set, all msb unset
            );
            t = msb_c & lsb_c; // for survival msb_ lsb_c will be one higher than needed as the base bit is counted
            lsb_c = msb_c & ~lsb_c;
            msb_c = t;
            board[0][i] |= m & // survive where current board is full IF:
            (
                ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
                (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) ) | // 2 neigbours : 2 lsb set, 0 msb set
                ( (any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 3 neigbours : 1 lsb set, 1 msb set OR
                ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) )     // 3 neigbours : all lsb set, all msb unset
            );
        }
    }
};