#include <cmath>
#include "GOL_RNG.h"

GOL_RNG::GOL_RNG(unsigned int seed_) {
    system = GOL_CRYPTO(64,8,seed_);
}

int GOL_RNG::rand_int(unsigned int max) {
    return system.rand_bits<32>().to_ulong() % max;
}

long GOL_RNG::rand_long(unsigned int max) {
    return system.rand_bits<64>().to_ulong() % max;
}

bool GOL_RNG::rand_bit() {
    return system.rand_bits<1>()[0];
}

double GOL_RNG::rand_double() {
	const static long sign_mask = ~((long) 3 << 62);
	const static long exp_mask = ((long) 1023 << 52);
    std::bitset bits = system.rand_bits<64>();
	bits &= sign_mask;
	bits |= exp_mask; 

    return *reinterpret_cast<double *>(&bits) - 1.0;
}

float GOL_RNG::rand_float() {
	const static int sign_mask = ~(3 << 30);
	const static int exp_mask = (127 << 23);
    std::bitset bits = system.rand_bits<32>();

	bits &= sign_mask;
	bits |= exp_mask; 

    return *reinterpret_cast<float *>(&bits) - 1.0;
}

void GOL_RNG::test() {
    for (int i =0; i < 100; i++) {
        system.step();
        system.print();
    }
}
