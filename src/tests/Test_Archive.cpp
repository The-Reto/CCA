#include "../../headers/CCA_Archive.h"


int main()
{
    CCA_Archive archiver("test");
    archiver.pack("./test_data", "./test_archive.tra");
    archiver.unpack("./test_archive.tra", "./unpack/");
}
