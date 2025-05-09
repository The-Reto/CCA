#include "../../headers/CCA_B_Dec.h"

bool CCA_B_Dec::put(Bit_Board<u_int64_t> buffer, int size) {
    if (size == BIT_BOARD_STREAM_BUFFER_SIZE) {
        key_buf = buffer;
        for (short i = ROUNDS-1; i > 0; i--) {
            update_F(buffer, 0, i);
            for (short j = 0; j<32; j++) {
                buffer[j + 32] ^= F[0][j];
            }
            update_F(buffer, 32, --i);
            for (short j = 0; j < 32; j++) {
                buffer[j] ^= F[0][j];
            }
        }
    }
    else {
        for (short i = 0; i < ROUNDS; i++) {
            update_F(key_buf, 32, i);
            for (short j = 0; j<32; j++) {
                key_buf[j] ^= F[0][j];
            }
            update_F(key_buf, 0, ++i);
            for (short j = 0; j<32; j++) {
                key_buf[j+32] ^= F[0][j];
            }
        }
        buffer = buffer ^ key_buf;
    }
    update_Key(key_buf);
    return next.put(buffer, size);
}