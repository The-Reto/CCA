#include "../headers/GOL_Enc.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Enc encryptor("test_password");
    GOL_Enc decryptor("test_password");
    std::string file = "test_data/test.txt";
    encryptor.encrypt(file);
    std::cout << "encrpyted" << std::endl;
    decryptor.decrypt(file+".enc");
    std::cout << "decrpyted" << std::endl;
}
