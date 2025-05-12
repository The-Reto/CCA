#include "../../headers/BitBoardOSink.h"

BitBoardOSink::BitBoardOSink(std::ostream& out) : out(out) {}

bool BitBoardOSink::put(Bit_Board<u_int64_t> buffer, int size) {
    out.write(reinterpret_cast<const char*>(&buffer), size);
    return out.good();
}

void BitBoardOSink::flush() {
    out.flush();
}