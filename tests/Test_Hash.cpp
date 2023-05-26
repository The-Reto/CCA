#include "../headers/GOL_Hash.h"
#include <fstream>
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Hash test("test_data/test.txt");
    test.get_graph_Hash().visualize();
    std::cout << test.get_Str_Hash() << std::endl;
}
