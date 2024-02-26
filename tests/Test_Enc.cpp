#include "../headers/GOL_Enc.h"
#include <boost/dynamic_bitset.hpp>

int main()
{
    GOL_Enc encryptor("test_password");
    GOL_Enc decryptor("test_password");
    std::string file = "test_data/test.mp3";
    encryptor.encrypt(file);
    std::cout << "encrpyted" << std::endl;
    std::string enc_file = file;
    enc_file.replace(enc_file.size()-4, 1, "-");
    decryptor.decrypt(enc_file+".trc");
    std::cout << "decrpyted" << std::endl;
}
