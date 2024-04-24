#include "./Neighbour_Counting_Board.h"

/// @brief A GOL-Board with flexible, customizable, rules - slower than a class where the rules are hardcoded
/// @tparam TYPE u_intX_t used to store the bord, simultaneously sets width of GOL-Board (eg. u_int32_t, sets the width to 32)
/// @tparam size height of the GOL-Board
template <class TYPE, int size> class Flexible_CA_Board: public Neighbour_Counting_Board<TYPE> {
    using Neighbour_Counting_Board<TYPE>::update_msb_lsb;
    using Neighbour_Counting_Board<TYPE>::board;
    using Neighbour_Counting_Board<TYPE>::noneof3;
    using Neighbour_Counting_Board<TYPE>::any1of3;
    using Neighbour_Counting_Board<TYPE>::any2of3;
    using Neighbour_Counting_Board<TYPE>::all3;

    public:

    bool survive[9] = {0,0,1,1,0,0,0,0,0}, create[9] = {0,0,0,1,0,0,0,0,0};

    /// @brief Default constructor, set the rules to "vanilla" Conway GOL 
    Flexible_CA_Board() {    }

    /// @brief Constructor, set the rules to custom GOL ruleset
    /// @param _survive survival rules, boolean array of length 9
    /// @param _create creation rules, boolean array of length 9
    Flexible_CA_Board(bool _survive[9], bool _create[9]): survive(_survive), create(_create) {

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
                create[0] * (noneof3(msb_o, msb_c, msb_u) & noneof3(lsb_c, lsb_o, lsb_u)) | // 0 neigbours : nothing set
                create[1] * ( noneof3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 1 neigbour : 0 msb set, 1 lsb set
                create[2] * ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
                (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
                create[3] * ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
                ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) | // 3 neigbours : all lsb set, all msb unset
                create[4] * ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
                (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) | // 4 neigbours : 2 msb set, no lsb set
                create[5] * ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
                ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 5 neigbours : 1 msb, 3 lsb
                create[6] * ( (all3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) | // 6 neigbours : 3 msb, no lsb
                ( any2of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) )) | // 6 neigbours : 2 msb, 2 lsb
                create[7] * ( (all3(msb_o, msb_u, msb_c) & any1of3(lsb_o, lsb_u, lsb_c) ) | // 7 neigbours : 3 msb, 1 lsb
                (any2of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 7 neigbours : 2 msb, 3 lsb 
                create[8] * (all3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c))   // 8 neigbours : 3 msb, 2 lsb
            );
            t = msb_c & lsb_c; // for survival msb_ lsb_c will be one higher than needed as the base bit is counted
            lsb_c = msb_c & ~lsb_c;
            msb_c = t;
            board[0][i] |= m & // survive where current board is full IF:
            (
                survive[0] * (noneof3(msb_o, msb_c, msb_u) & noneof3(lsb_c, lsb_o, lsb_u)) | // 0 neigbours : nothing set
                survive[1] * ( noneof3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 1 neigbour : 0 msb set, 1 lsb set
                survive[2] * ( (noneof3(lsb_o, lsb_u, lsb_c) & any1of3(msb_o, msb_u, msb_c)) | // 2 neigbors : 1 msb set, 0 lsb set OR
                (noneof3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) ) ) | // 2 neigbours : 2 lsb set, 0 msb set
                survive[3] * ( ( any1of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c) ) | // 3 neigbours : 1 lsb set, 1 msb set OR
                ( noneof3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c)) ) | // 3 neigbours : all lsb set, all msb unset
                survive[4] * ( (any1of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c)) | // 4 neigbours : 1 msb set, 2 lsb set OR
                (any2of3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) ) | // 4 neigbours : 2 msb set, no lsb set
                survive[5] * ( (any2of3(msb_o, msb_u, msb_c) & any1of3(lsb_u, lsb_o, lsb_c)) | // 5 neigbours : two msb set, 1 lsb OR
                ( any1of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 5 neigbours : 1 msb, 3 lsb
                survive[6] * ( (all3(msb_o, msb_u, msb_c) & noneof3(lsb_o, lsb_u, lsb_c)) | // 6 neigbours : 3 msb, no lsb
                ( any2of3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c) )) | // 6 neigbours : 2 msb, 2 lsb
                survive[7] * ( (all3(msb_o, msb_u, msb_c) & any1of3(lsb_o, lsb_u, lsb_c) ) | // 7 neigbours : 3 msb, 1 lsb
                (any2of3(msb_o, msb_u, msb_c) & all3(lsb_o, lsb_u, lsb_c) ) ) | // 7 neigbours : 2 msb, 3 lsb 
                survive[8] * (all3(msb_o, msb_u, msb_c) & any2of3(lsb_o, lsb_u, lsb_c))   // 8 neigbours : 3 msb, 2 lsb
            );
        }
    }

    /// @brief Used to set survival rules for the Neighbour_Counting_Board. 
    /// @param _survive boolean array of length 9, position indicates number of neighbours
    void set_survive(bool _survive[9]) {
        for (int i = 0; i < 9; i++) {
            survive[i] = _survive[i];
        }
    }

    /// @brief Used to set creation rules for the Neighbour_Counting_Board.
    /// @param _create boolean array of length 9, position indicates number of neighbours
    void set_create(bool _create[9]) {
        for (int i = 0; i < 9; i++) {
            create[i] = _create[i];
        }
    }

    /// @brief Used to set survival and creation rules for the Neighbour_Counting_Board.
    /// @param _survive boolean array of length 9, position indicates number of neighbours
    /// @param _create boolean array of length 9, position indicates number of neighbours
    void set_rules(bool _survive[9], bool _create[9]) {
        set_survive(_survive);
        set_create(_create);
    }
};