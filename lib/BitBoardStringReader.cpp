#include "../include/BitBoardStringReader.h"

BitBoardStringReader::BitBoardStringReader(const std::string& string) : str_stream(string) {

}

bool BitBoardStringReader::run(BitBoardStreamBuf& sink) {
    while (str_stream.read(reinterpret_cast<char*>(&buffer), BIT_BOARD_STREAM_BUFFER_SIZE)) {
        sink.put(buffer, BIT_BOARD_STREAM_BUFFER_SIZE);
    }
    std::streamsize remaining = str_stream.gcount();
    if (remaining > 0) {
        sink.put(buffer, remaining);
    }
    return true;
}