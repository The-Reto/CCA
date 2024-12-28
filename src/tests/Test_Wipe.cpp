#include "../../headers/CCA_Wiper.h"
#include <fstream>
#include <filesystem>

int main()
{
    std::string path = "test_data/Wipe_test.txt", seed = "this is a seed";
    CCA_Wiper::wipe(path, seed, 1);
}
