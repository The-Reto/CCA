#include <cmath>
#include "GOL_RNG.h"

int test(int seed) {
    static const int range = 20, avg=100;
    GOL_RNG test(seed);
    
    int samples = range*avg;
    int results[range] = {0};
    
    for (int i = 0; i < samples; i++) {
        //results[(int) std::floor(test.rand_double() * range)]++;
        results[test.rand_int(range)]++;
    }
    for (int i =0; i < range; i++) {
        std::cout << results[i] << " ";
        if (results[i] < avg) {std::cout << " ";}
    }
    return test.rand_int();
}

int demo(unsigned int seed) {
    GOL_RNG a(seed ^ 3141591);
    for (int i = 0; i < 15; i++) {
    	std::cout << a.rand_double() << " ";
    }
    return a.rand_int();
}

int main()
{
    int seed = 22051996;
    
    for(int i = 0; i < 10; i++) {
        seed = test(seed);
        //seed = demo(seed);
        std::cout << std::endl;
    }
    

}
