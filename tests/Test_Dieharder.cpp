#include "../include/CCA_Key.h"
#include <chrono>

int main(int argc, char *argv[])
{
    CCA_Key test_a = CCA_Key::generate_key(argv[1]);
    int res = 0;
    Bit_Board<u_int64_t> out = test_a.get_board();
    out[0] ^= 0x10000000;
    CCA_Key test_b(out);
    out.reset();
    while (true) {
        out = *test_a.get_streched_key() ^ *test_b.get_streched_key();
        res = write(1,&out,512);
    }
}