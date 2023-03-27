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

class GOL {
    protected:
    bool * board;
    bool * buff_board;
    int sizex, sizey;
    bool survive[9] = {0,0,1,1,0,0,0,0,0};
    bool create[9] =  {0,0,0,1,0,0,0,0,0};
    
    int count_neighbours(int x, int y) {
        int neighbours = -get(x, y);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                neighbours += get(x + i, y + j);
            }
        }
        return neighbours;
    }
    
    bool get(int x, int y) {
        int x_ = (x + sizex) % sizex;
        int y_ = (y + sizey) % sizey;
        return board[ y_ * sizex + x_];
    }
    
    void set(int x, int y, bool val) {
        int x_ = x % sizex;
        int y_ = y % sizey;
        if (x < 0) { x_ = sizex + x; }
        if (y < 0) { y_ = sizey + y; }
        board[ y_ * sizex + x_] = val;
    }
    
    public:
    GOL(int sizex_, int sizey_, unsigned int seed) : sizex(sizex_), sizey(sizey_) {
        board = new bool [sizex * sizey];
        buff_board = new bool [sizex * sizey];
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            board[i] = s[i];
        }
    }
    
    void step() {
        for (int i = 0; i < sizex; i++) {
            for (int j = 0; j < sizey; j++) {
                int neighbours = count_neighbours(i,j);
                buff_board[j * sizex + i] = get(i,j) * survive[neighbours] + (1 -  get(i,j)) * create[neighbours];
            }
        }
        memcpy(board, buff_board, sizex * sizey);
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
                if (get(i,j)) {
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

class GOL_CRYPTO: public GOL {
    protected:
    unsigned int seed;
    
    bool* create_seed_map() {
        bool* map = new bool [sizex * sizey];
        std::bitset s = std::bitset<sizeof( int )*CHAR_BIT>(seed);
        for (int i = sizex/5; i < sizex; i++) { //adding noise
            for (int j = sizey/4; j < sizey/2; j++) {
                map[j * sizex + i] = s[(i*j+j) % (sizeof( int )*CHAR_BIT)];
            }
        }
        return map;
    }
    
    void set_rules(bool choice) {
        bool survive_[18] = {0,0,1,1,0,1,0,0,0, 0,0,1,0,1,1,1,0,1};
        bool create_[18] =  {0,0,1,0,1,1,0,0,0, 0,0,1,0,1,0,1,0,1};
        for (int i = 0 + choice*9; i < 9 + choice*9; i++) {
            survive[i] = survive_[i];
            create[i] = create_[i];
        }
    }

    public:
    GOL_CRYPTO(int sizex_, int sizey_, unsigned int seed_) : GOL(sizex_, sizey_, seed_) {
        seed = (seed_ + 3141592) % INT_MAX;

        set_rules(seed % 2);
        apply_xormap(create_seed_map(), sizex, sizey);
        steps(5*sizex*sizey); // distribute seed
    }
    
    GOL_CRYPTO() : GOL(32,32,0) {
        GOL_CRYPTO(32, 32, 0);
    }
    
    std::bitset<sizeof( int )*CHAR_BIT> rand_bits() {
        unsigned int ret = 0;
        for (int i = 0; i < sizeof( int )*CHAR_BIT; i++) {
            ret |= get(3*i+seed, seed/3) << (sizex - i - 1);
        }
        step();
        seed = (seed ^ ret);
        set_rules(ret % 2);
        return std::bitset<sizeof( int )*CHAR_BIT>(ret);
    }
    
    unsigned int get_seed() {
        return seed;
    }
    
    void apply_xormap(bool * map, int x, int y) {
        for (int i = 0; i < x; i++) { //adding noise
            for (int j = 0; j < y; j++) {
                set(i,j, get(i,j)^map[j * x + i]);
            }
        }
    }
};

class GOL_RNG {
    
    GOL_CRYPTO system;

    public:
    GOL_RNG(unsigned int seed_) {
        system = GOL_CRYPTO(32, 7, seed_);
    }
    
    unsigned int rand_int(unsigned int max = INT_MAX) {
        return system.rand_bits().to_ulong() % max;
    }
    
    bool rand_bit() {
        return system.rand_bits()[0];
    }
    
    float uniform() {
    	int sign_mask = ~(3 << 30);
    	int exp_mask = (127 << 23);
        std::bitset bits = system.rand_bits();

    	bits &= sign_mask;
    	bits |= exp_mask; 

        return *reinterpret_cast<float *>(&bits) - 1.0;
    }
};

int test(int seed) {
    GOL_RNG test(seed);
    
    int samples = 10;
    
    for (int i = 0; i < samples; i++) {
        std::cout << test.uniform() << ", " << test.uniform() << std::endl;
    }
    return test.rand_int();
}

int main()
{
    unsigned int seed = 31415;

    for (int i = 0; i < 20; i++) {
        seed = test(seed);
    }
}
