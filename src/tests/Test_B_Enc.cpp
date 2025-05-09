#include "../../headers/CCA_B_Enc.h"
#include "../../headers/CCA_B_Dec.h"
#include "../../headers/BitBoardFileWriter.h"
#include "../../headers/BitBoardFileReader.h"
#include <boost/dynamic_bitset.hpp>
#include <iostream>

int main()
{
    BitBoardFileWriter out("./test_data/test.trc");
    CCA_B_Enc encryptor(out, "test_password");
    BitBoardFileReader file("./test_data/test.txt");
    file.run(encryptor);
    out.flush();
    BitBoardFileWriter out1("./test_data/test-dec.txt");
    CCA_B_Dec decryptor(out1, "test_password");
    BitBoardFileReader file1("./test_data/test.trc");
    file1.run(decryptor);
}
