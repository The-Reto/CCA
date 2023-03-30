#include <cmath>
#include "GOL_RNG.h"

int test(int seed) {
    static const int range = 10;
    GOL_RNG test(seed);
    
    int samples = range*10000;
    int results[range] = {0};
    
    for (int i = 0; i < samples; i++) {
        int index = std::floor(test.rand_float() * range);
        results[index]++;
    }
    for (int i =0; i < range; i++) {
        std::cout << results[i] << " ";
        if (results[i] < 100000) {std::cout << " ";}
    }
    return test.rand_int();
}

void demo() {
    GOL_RNG a(3141591), b(22051996), c(16091999);
    for (int i = 0; i < 1000; i++) {
        std::cout << a.rand_int(100) << " " << b.rand_int(100) << " " << c.rand_int(100) << " " << std::endl;
    }
}

int main()
{
    int seed = 22051996;
    
    demo();
    
    //for(int i = 0; i < 5; i++) {
    //    seed = test(seed);
    //    std::cout << std::endl;
    //}
    //demo();

}
