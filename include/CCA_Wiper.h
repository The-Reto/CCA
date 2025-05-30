#ifndef GOL_WIPE_H
#define GOL_WIPE_H
#include "CCA_Key.h"
#include <fstream>
#include <fstream>
#include <filesystem>


class CCA_Wiper {    
    public:
    static const short BLOCK_SIZE = 64*64;

    static void wipe(std::string path, std::string seed, short repetitions = 8);
    
};
#endif
