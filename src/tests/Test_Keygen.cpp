#include "../../headers/CCA_Keygen.h"
#include "../../headers/Flexible_CA_Board.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    CCA_Keygen test("a");

    for (long i = 0; i < 10; i++) {
    std::cout << test.get_streched_key()[0] << std::endl;
    }
}
