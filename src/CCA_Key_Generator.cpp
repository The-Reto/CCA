#include "../include/CCA_Key.h"

int main(int argc, char *argv[]){
    std::string output_path = argv[1], rand_user_data = argv[2];
    CCA_Key::write_key_to_file(CCA_Key::generate_key(rand_user_data), output_path);
}