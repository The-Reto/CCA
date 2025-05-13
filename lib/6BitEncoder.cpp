#include "../include/6BitEncoder.h"

SixBitEncoder::SixBitEncoder(std::ostream& _out) : BitBoardOSink(_out)
{
}

bool SixBitEncoder::put(Bit_Board<u_int64_t> buffer, int size) {
    u_int8_t out_char = 0, position = 0;
    u_int32_t bits_outputted = 0, bits_outputted_round = 0;

    while (bits_outputted + 6 <= size * 8)
    {   
        bits_outputted += 6;
        if (bits_outputted_round + 6 <= 64) {
            bits_outputted_round += 6;
            out.put( symbols[ (buffer[position] >> (64 - bits_outputted_round)) & 0x3F ] );
        }
        else {
            short diff = 64 - bits_outputted_round;
            out_char = ( (buffer[position]) << (6 - diff) ) & 0x3F;
            out_char |= (buffer[++position] >> (64 - 6 + diff));
            out.put( symbols[out_char] );
            bits_outputted_round = 6 - diff;
        }
    }
    u_int8_t buffered = 8*size - bits_outputted;
    out.put(symbols[( (buffer[position]) << (6 - buffered) )  & 0x3F]);
    return out.good();
}