#include <iostream>
#include <bitset>
#include <climits>
#include <cstring>
#include <chrono>
#include <thread>
#include <stdexcept>


template <int sizex, int sizey> class BitBoard{
    int len;
    std::bitset< sizex * sizey > board, neighbour_mask;
    const static int Moore_len = 8, vNeumann_len = 4;
    const int Moore_Neighbours[Moore_len] = { -sizex-1, -sizex, -sizex+1, -1, 1, sizex-1, sizex, sizex+1 };
    const int vNeumann_Neighbours[vNeumann_len] = { -sizex, -1, 1, sizex };

    
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
    
    void set(int index, bool val) {
        while (index < 0) {index += len;}
        index = index % len;
        board[index] = val;
    }
    
    public:
    BitBoard() {
        len = sizex * sizey;
        for (int i = 0; i < Moore_len; i++) {
            int index = Moore_Neighbours[i];
		    while (index < 0) {index += len;}
		    index = index % len;
            neighbour_mask[index] = true;
        }
    }
    
    BitBoard& operator = (const BitBoard& other) {
        board = other.board;
        neighbour_mask = other.neighbour_mask;
        return *this;
    }
    
    std::bitset<sizex*sizey> get() {
        return board;
    }
    
    inline bool get(int x, int y) {
        return board[ xy_to_l(x,y) ];
    }
    
    void set(std::bitset<sizex*sizey> map) {
        for (int i = 0; i<len; i++) {
            set(i, map[i]);
        }
    }
    
    void set(int x, int y, bool val) {
        board[ xy_to_l(x,y) ] = val;
    }
    
    inline int count_neighbours(int l) {
        return (board & ( (neighbour_mask << l) | (neighbour_mask >> (len - l)) )).count();
    }
    
    inline int count_neighbours(int x, int y) { return count_neighbours(xy_to_l(x,y)); }
    
    const inline int get_sizex() {return sizex;}
    const inline int get_sizey() {return sizey;}
};

template <int sizex, int sizey> class GOL {
    protected:
    BitBoard<sizex, sizey>  board,  b_board;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    public:
    GOL(unsigned int seed) {
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            board.set(5,i+3, s[i]);
        }
    }
    
    void test() {
        std::cout << board.count_neighbours(5,4);
    }
    
    void step() {
        for (int i = 0; i < sizex; i++) {
            for (int j = 0; j < sizey; j++) {
                int neighbours = board.count_neighbours(i,j);
                b_board.set(i, j, board.get(i,j) * survive[neighbours] + (1 -  board.get(i,j)) * create[neighbours] );
            }
        }
        board.set(b_board.get());
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
                    //std::cout << board.count_neighbours(i, j) << " ";
                }
                else {
                    std::cout << "\u25A2 ";
                    //std::cout << board.count_neighbours(i, j) << " ";
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
    
    GOL<32,32> gol(415003079);
    
    gol.print();
    gol.step();
    gol.print();
    gol.step();
    gol.print();
    gol.step();

    for (int i = 0; i < 20; i++) {
        seed = test(seed);
    }
}
