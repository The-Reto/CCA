#include "../include/CCA_B_Enc.h"
#include "../include/CCA_B_Dec.h"
#include "../include/BitBoardFileWriter.h"
#include "../include/BitBoardFileReader.h"
#include "../include/CCA_Hash.h"
#include <boost/dynamic_bitset.hpp>
#include <iostream>

int main()
{
    BitBoardFileWriter out1("./test_data/output/test-dec-ctb.txt");
    CCA_B_Dec decryptor(out1, "./test_data/test.ctk");
    BitBoardFileReader file1("./test_data/test.ctb");
    file1.run(decryptor);
}
