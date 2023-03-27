#include <iostream>
#include <bitset>
#include <climits>
#include <cstring>
#include <chrono>
#include <thread>


template <int sizex, int sizey> class BitBoard{
    int len;
    std::bitset< sizex * sizey > board();
    const int neighbour_mask[8] = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    
    int xy_to_l(int x, int y) {
        while (x < 0) {x += sizex;}
        while (y < 0) {y += sizey;}
        x = x % sizex;
        y = y % sizey;
        return y * sizex + x;
    }
    
    bool get(int index) {
        while (index < 0) {index += len;}
        index = index % len;
        return board[index];
    }
    
    public:
    BitBoard() {
        len = sizex * sizey;
    }
    
    bool get(int x, int y) {
        return board[ xy_to_l(x,y) ];
    }
    
    void set(int x, int y, bool val) {
        board[ xy_to_l(x,y) ] = val;
    }
    
    int count_neighbours(int x, int y) {
        int neighbours = 0;
        int l = xy_to_l(x,y);
        for (int i = 0; i <= 8; i++) {
            neighbours += get( l + neighbour_mask[i] );
        }
        return neighbours;
    }
};

template <int sizex, int sizey> class GOL {
    protected:
    BitBoard<sizex, sizey>  board;
    BitBoard<sizex, sizey> buff_board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    public:
    GOL(unsigned int seed) {
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            board[i] = s[i];
        }
    }
    
    void step() {
        for (int i = 0; i < sizex; i++) {
            for (int j = 0; j < sizey; j++) {
                int neighbours = board.count_neighbours(i,j);
                buff_board.set(i,j) = board.get(i,j) * survive[neighbours] + (1 -  board.get(i,j)) * create[neighbours];
            }
        }
        memcpy(board, buff_board, sizeof(BitBoard<sizex, sizey>));
    }
    
    void steps(int steps){
        for (int i = 0; i < steps; i++) {
            step();
        }
    }
    
    void print() {
        std::cout << "\u250f\u2501";
        for (int i = 0; i < sizey; i++) {
            std::cout << "\u2501\u2501";
        }
        std::cout << "\u2501\u2513\n";
        for (int i = 0; i < sizex; i++) {
            std::cout << "\u2503 ";
            for (int j = 0; j < sizey; j++) {
                if (board.get(i,j)) {
                    std::cout << "\u25A0 ";
                }
                else {
                    std::cout << "\u25A2 ";
                }
            }
            std::cout << " \u2503\n";
        }
        std::cout << "\u2517\u2501";
        for (int i = 0; i < sizey; i++) {
            std::cout << "\u2501\u2501";
        }
        std::cout << "\u2501\u251b\n";
    }
    
    bool* get_board() {
        return board;
    }
};


int test(int seed) {
    //GOL_RNG test(seed);
    
    int samples = 10;
    
    for (int i = 0; i < samples; i++) {
        //std::cout << test.uniform() << ", " << test.uniform() << std::endl;
    }
    return 0;//test.rand_int();
}

int main()
{
    unsigned int seed = 31415;

    for (int i = 0; i < 20; i++) {
        seed = test(seed);
    }
}
