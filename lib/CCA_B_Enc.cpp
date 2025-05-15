#include "../include/CCA_B_Enc.h"

CCA_B_Enc::CCA_B_Enc(BitBoardStreamBuf& _next, std::string _key, Bit_Board<u_int64_t> _iv)  : CCA_B(_next, _key) {
    put(_iv);
}

bool CCA_B_Enc::put(Bit_Board<u_int64_t> buffer, int size) {
    if (size == BIT_BOARD_STREAM_BUFFER_SIZE) {
        for (short i = 0; i < ROUNDS; i++) {
            update_F(buffer, 32, i);
            for (short j = 0; j<32; j++) {
                buffer[j] ^= F[0][j];
            }
            update_F(buffer, 0, ++i);
            for (short j = 0; j<32; j++) {
                buffer[j+32] ^= F[0][j];
            }
        }
        prev = buffer;
    }
    else {
        for (short i = 0; i < ROUNDS; i++) {
            update_F(prev, 32, i);
            for (short j = 0; j<32; j++) {
                prev[j] ^= F[0][j];
            }
            update_F(prev, 0, ++i);
            for (short j = 0; j<32; j++) {
                prev[j+32] ^= F[0][j];
            }
        }
        buffer = buffer ^ prev;
    }
    update_Key(prev);
    return next.put(buffer, size);
}