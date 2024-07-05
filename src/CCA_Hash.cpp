#include <iostream>
#include <filesystem>
#include "../headers/CCA_Hash.h"

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[]){ // call -f in-file -m MODE -k Key -o out-file
    bool strMode = cmdOptionExists(argv, argv+argc, "-s");
    unsigned long size = 0;

    if (strMode) {
        std::istringstream stream(argv[argc-1]);
        size = std::strlen(argv[argc-1]);
        CCA_Hash hash(stream, size);
        std::cout << hash.get_Str_Hash() << std::endl;        
    }
    else {
        std::basic_ifstream<char> stream(argv[argc-1]);
        size = std::filesystem::file_size(argv[argc-1]);
        CCA_Hash hash(stream, size);
        std::cout << hash.get_Str_Hash() << std::endl;        
    }

}