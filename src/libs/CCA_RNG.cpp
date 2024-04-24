#include <cmath>
#include "../../headers/CCA_RNG.h"

CCA_RNG::CCA_RNG(unsigned int seed_) :     system(CCA_Board(seed_)) {

}

int CCA_RNG::rand_int(unsigned int max) {
    if (int_ctr >= 128) {
        int_ctr = -1;
        int_board = system[0];
        system.step();
    }
    int_ctr += 1;
    if (int_ctr % 2 == 0) {
        return ((uint32_t) (int_board[int_ctr/2] >> 32)) % max;
    }
    else {
        return ((uint32_t) int_board[(int_ctr-1)/2]) % max;
    }
}

long CCA_RNG::rand_long(unsigned long max) {
    if (long_ctr >= 64) {
        long_ctr = 0;
        long_board = system[0];
        system.step();
    }
    return long_board[long_ctr++] % max;
}

bool CCA_RNG::rand_bit() {
    if (bit_ctr >= 4096) {
        bit_ctr = 0;
        bit_board = system[0];
        system.step();
    }
    return bit_board.get(bit_ctr%64, bit_ctr/64);
}

double CCA_RNG::rand_double() {
	const static long sign_mask = ~((long) 3 << 62);
	const static long exp_mask = ((long) 1023 << 52);
    u_int64_t bits = rand_long();
	bits &= sign_mask;
	bits |= exp_mask; 
    return *reinterpret_cast<double *>(&bits) - 1.0;
}

float CCA_RNG::rand_float() {
	const static int sign_mask = ~(3 << 30);
	const static int exp_mask = (127 << 23);
    u_int32_t bits = rand_int();
	bits &= sign_mask;
	bits |= exp_mask; 
    return *reinterpret_cast<float *>(&bits) - 1.0;
}

void CCA_RNG::test() {
    for (int i =0; i < 100; i++) {
        system.step();
        system.visualize();
    }
}
