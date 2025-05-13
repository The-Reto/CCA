#include "../include/CCA_Keygen.h"
#include <chrono>

int main(int argc, char *argv[])
{
    CCA_Keygen test_a(argv[1]);
    int res = 0;
    while (true) {
         res = write(1,&test_a.get_streched_key()[0],512);
    }
}