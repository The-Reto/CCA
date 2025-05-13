#include "../include/CCA_Hash.h"
#include "../include/BitBoardOSink.h"
#include "../include/BitBoardFileReader.h"
#include "../include/BitBoardStringReader.h"

int main()
{
    BitBoardOSink out(std::cout);
    CCA_Hash hasher_file, hasher_string;
    BitBoardFileReader file("./test_data/test.txt");
    BitBoardStringReader str("this is a very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very vory very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very very long test string");
    file.run(hasher_file);
    //out.put(hasher_file.get_Hash());

    str.run(hasher_string);
    out.put(hasher_string.get_Hash());
}
