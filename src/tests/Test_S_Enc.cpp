#include "../../headers/CCA_S_Enc.h"
#include "../../headers/BitBoardFileWriter.h"
#include "../../headers/BitBoardFileReader.h"
#include <boost/dynamic_bitset.hpp>
#include <fstream>

int main()
{
    BitBoardFileWriter out("./test_data/test.trc");
    CCA_S_Enc encryptor(out, "test_password");
    BitBoardFileReader file("./test_data/test.txt");
    file.run(encryptor);

    BitBoardFileWriter out1("./test_data/test-dec.txt");
    CCA_S_Enc decryptor(out1, "test_password");
    BitBoardFileReader file1("./test_data/test.trc");
    file1.run(decryptor);
}
