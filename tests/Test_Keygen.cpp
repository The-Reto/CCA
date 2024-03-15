#include "../headers/GOL_Keygen.h"
#include "../headers/Flexible_GOL_Board.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Keygen test("a");

    for (long i = 0; i < 10; i++) {
    std::cout << test.get_streched_key()[0] << std::endl;
    }
}
