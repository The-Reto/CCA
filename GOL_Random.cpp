#include "GOL_Crypto.cpp"
#include <cmath>

class GOL_RNG {
    
    GOL_CRYPTO<32,8> system;

    public:
    GOL_RNG(unsigned int seed_) {
        system = GOL_CRYPTO<32,8>(seed_);
    }
    
    unsigned int rand_int(unsigned int max = INT_MAX) {
        return system.rand_bits().to_ulong() % max;
    }
    
    bool rand_bit() {
        return system.rand_bits()[0];
    }
    
    float uniform() {
    	const static int sign_mask = ~(3 << 30);
    	const static int exp_mask = (127 << 23);
        std::bitset bits = system.rand_bits();

    	bits &= sign_mask;
    	bits |= exp_mask; 

        return *reinterpret_cast<float *>(&bits) - 1.0;
    }
    
};

int test(int seed) {
    static const int range = 20;
    GOL_RNG test(seed);
    
    int samples = range*10000;
    int results[range] = {0};
    
    for (int i = 0; i < samples; i++) {
        int index = std::floor(test.uniform() * range);
        results[index]++;
    }
    for (int i =0; i < range; i++) {
        std::cout << results[i] << " ";
        if (results[i] < 10000) {std::cout << " ";}
    }
    return test.rand_int();
}

int main()
{
    int seed = 22051996;
    
    for(int i = 0; i < 5; i++) {
        seed = test(seed);
        std::cout << std::endl;
    }

}
