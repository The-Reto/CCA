#include "../../headers/CCA_Hash.h"
#include <fstream>
#include <filesystem>

#include <boost/dynamic_bitset.hpp>

int main()
{
    std::basic_ifstream<char> stream("test_data/test.txt");
    CCA_Hash test(stream, std::filesystem::file_size("test_data/test.txt"));
    test.print_graph_Hash();
    std::cout << test.get_Str_Hash() << std::endl;
    std::cout << test.get_Hash() << std::endl;
}
