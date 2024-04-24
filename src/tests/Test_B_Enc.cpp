#include "../../headers/CCA_B_Enc.h"
#include <boost/dynamic_bitset.hpp>
#include <iostream>

int main()
{
    CCA_B_Enc encryptor("test_password");
    CCA_B_Enc decryptor("test_password");
    std::string ifile = "test_data/test.txt";
    std::string ofile = "test_data/test-txt.trc";
    std::string o2file = "test_data/test-DEC.txt";
    encryptor.encrypt(ifile, ofile);
    std::cout << "encrpyted" << std::endl;

    decryptor.decrypt(ofile, o2file);
    std::cout << "decrpyted" << std::endl;
}
