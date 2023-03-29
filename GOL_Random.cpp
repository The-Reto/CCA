#include "GOL_Crypto.cpp"

class GOL_RNG {
    
    GOL_CRYPTO<32,32> system;

    public:
    GOL_RNG(unsigned int seed_) {
        std::cout << "Init GOL_RNG..." << std::endl;
        system = GOL_CRYPTO<32,32>(seed_);
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
    
    int samples = 2;
    
    for (int i = 0; i < samples; i++) {
        std::cout << test.uniform() << ", " << test.uniform() << std::endl;
    }
    return test.rand_int();
}

int main()
{
    unsigned int seed = 31415;
    
    GOL_RNG test(seed);
    std::cout << test.uniform() << ", " << test.uniform() << std::endl;

    //for (int i = 0; i < 2; i++) {
        //seed = test(seed);
    //}
}
