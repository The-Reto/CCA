#ifndef GOL_ARCHIVE_H
#define GOL_ARCHIVE_H
#include "CCA_Hash.h"
#include "CCA_S_Enc.h"

#include <fstream>
#include <fstream>
#include <filesystem>


class CCA_Archive {    
    public:
    static const short BLOCK_SIZE = 64*64;

    CCA_Archive(std::string key);

    void pack(std::string in_path, std::string out_path);
    void unpack(std::string in_path, std::string out_path);
    private:
    std::string salt, key;
};
#endif
