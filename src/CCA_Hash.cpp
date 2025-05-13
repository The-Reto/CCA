#include "../include/CCA_Hash.h"
#include "../include/BitBoardFileReader.h"
#include "../include/BitBoardStringReader.h"
#include "../include/6BitEncoder.h"

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[]){ 
    bool strMode = cmdOptionExists(argv, argv+argc, "-s");
    unsigned long size = 0;
    CCA_Hash hasher;
    SixBitEncoder out(std::cout);
    if (strMode) {
        BitBoardStringReader str_stream(argv[argc-1]);    
        str_stream.run(hasher);        
    }
    else {
        BitBoardFileReader file(argv[argc-1]);    
        file.run(hasher);
    }
    out.put(hasher.get_Hash());
    std::cout << std::endl;
}