#include "../../headers/BitBoardFileReader.h"

BitBoardFileReader::BitBoardFileReader(const std::string& filename) : file(filename, std::ios::binary) {}
    
bool BitBoardFileReader::isOpen() const { return file.is_open(); }
    
bool BitBoardFileReader::run(BitBoardStreamBuf& sink) {
    if (!file) return false;
    file.clear();
    file.seekg(0, std::ios::beg);

    while (file.read(reinterpret_cast<char*>(&buffer), BIT_BOARD_STREAM_BUFFER_SIZE)) {
        sink.put(buffer, BIT_BOARD_STREAM_BUFFER_SIZE);
    }
    std::streamsize remaining = file.gcount();
    if (remaining > 0) {
        sink.put(buffer, remaining);
    }
    return true;
}