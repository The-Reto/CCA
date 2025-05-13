#include "../include/CCA_S_Enc.h"

CCA_S_Enc::CCA_S_Enc(BitBoardStreamBuf& _next, std::string _key) : next(_next), key_manager(_key) {}

bool CCA_S_Enc::put(Bit_Board<u_int64_t> buffer, int size) {
    return next.put(buffer ^ *key_manager.get_streched_key(), size);
}
