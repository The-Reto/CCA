#include "GOL_Crypto.cpp"

class GOL_RNG {
    
    GOL_CRYPTO<32,16> system;

    public:
    GOL_RNG(unsigned int seed_) {
        system = GOL_CRYPTO<32,16>(seed_);
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
    
    int samples = 2000;
    int results[2] = {0,0};
    
    for (int i = 0; i < samples; i++) {
        results[test.rand_bit()]++;
    }
    std::cout << results[0] << " " << results[1];
    return test.rand_int();
}

int main()
{
    int seed = 31415;
    
    for(int i = 0; i < 20; i++) {
        seed = test(seed);
        std::cout << std::endl;
    }

}
