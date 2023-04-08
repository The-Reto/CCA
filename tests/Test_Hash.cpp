#include "../headers/GOL_Hash.h"
#include <fstream>
#include <boost/dynamic_bitset.hpp>

int main()
{
    std::ifstream file("test.txt", std::ios::binary);

    GOL_Hash test(file);
    test.get_Hash().visualize();
}
