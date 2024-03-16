#include "../headers/GOL_Enc.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Enc encryptor("test_password");
    GOL_Enc decryptor("test_password");
    std::string in_file = "test_data/test.mp4";
    std::string out_file = "test_data/testvideo.trc";
    std::string out2_file = "test_data/testvideoDEC.mp4";
    encryptor.encrypt(in_file, out_file);
    std::cout << "encrpyted" << std::endl;

    decryptor.encrypt(out_file, out2_file);
    std::cout << "decrpyted" << std::endl;
}
