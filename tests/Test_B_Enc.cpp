#include "../include/CCA_B_Enc.h"
#include "../include/CCA_B_Dec.h"
#include "../include/BitBoardFileWriter.h"
#include "../include/BitBoardFileReader.h"
#include "../include/CCA_Hash.h"
#include <boost/dynamic_bitset.hpp>
#include <iostream>

int main()
{
    BitBoardFileReader file("./test_data/test.txt");
    BitBoardFileWriter out("./test_data/test.trc");
    CCA_Hash hasher;
    file.run(hasher);
    CCA_B_Enc encryptor(out, "./test_data/test_key.trk", hasher.get_Hash());
    file.run(encryptor);
    out.flush();
    BitBoardFileWriter out1("./test_data/test-dec.txt");
    CCA_B_Dec decryptor(out1, "./test_data/test_key.trk");
    BitBoardFileReader file1("./test_data/test.trc");
    file1.run(decryptor);
}
