#include "../include/CCA_Key.h"

int main()
{
    std::string line;
    std::getline( std::cin, line );
    CCA_Key test = CCA_Key::generate_key(line);

    Bit_Board<u_int64_t>::visualize(*test.get_key());

    CCA_Key::write_key_to_file(test, "./test_data/test_key.trk");
}
