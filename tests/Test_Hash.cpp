#include "../headers/GOL_Hash.h"
#include <fstream>
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Hash test("test_data/test.txt");
    test.print_graph_Hash();
    std::cout << test.get_Str_Hash() << std::endl;
    std::cout << test.get_Hash() << std::endl;
}
