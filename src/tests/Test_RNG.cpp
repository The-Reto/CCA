#include <cmath>
#include "../../headers/CCA_RNG.h"

int test(int seed) {
    static const int range = 20, avg=5000;
    CCA_RNG test(seed);
    
    int samples = range*avg;
    int results_int[range] = {0};
    int results_float[range] = {0};
    
    std::cout << "Testing uniform distribution by pooling results into bins:" << std::endl;
    
    for (int i = 0; i < samples; i++) {
        results_float[(int) std::floor(test.rand_double() * range)]++;
        results_int[test.rand_int(range)]++;
    }
    std::cout << "For Integers: ";
    for (int i =0; i < range; i++) {
        std::cout << results_int[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "For Floats:   ";
    for (int i =0; i < range; i++) {
        std::cout << results_float[i] << " ";
    }
    std::cout << std::endl;
    return test.rand_int();
}

int demo(unsigned int seed) {
    CCA_RNG a(seed ^ 3141591);
    std::cout << "Showing sample uniform distribution:" << std::endl;
    std::cout << "For Floats:   ";
    for (int i = 0; i < 15; i++) {
    	std::cout << 100*a.rand_double() << " ";
    }
    std::cout << std::endl;
    std::cout << "For Integers: ";
    for (int i = 0; i < 15; i++) {
    	std::cout << a.rand_int(100) << " ";
    }
    std::cout << std::endl;
    return a.rand_int();
}

int main()
{
    unsigned long seed = 3141592;
    for(int i = 0; i < 3; i++) {
        std::cout << "Testing for seed: " << seed << std::endl;
        seed = test(seed);
        demo(seed);
        std::cout << "============================================================================================================================" << std::endl;
    }

}
