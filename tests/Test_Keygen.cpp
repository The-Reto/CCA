#include "../headers/GOL_Keygen.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Keygen test("test_password");
    std::cout << test.get_streched_key(2000) << std::endl;
    std::cout << test.get_streched_key(2000) << std::endl;
}
