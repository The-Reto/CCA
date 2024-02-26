#include "../headers/GOL_Enc.h"

GOL_Enc::GOL_Enc(std::string key) : key_manager(key) {}

void GOL_Enc::scramble_block(int blockSize) {
    input_stream.read(buffer.data(), blockSize);
    boost::dynamic_bitset<unsigned char> data = boost::dynamic_bitset<unsigned char>(buffer.begin(), buffer.end());
    data ^= key_manager.get_streched_key(data.size());
    std::vector<unsigned char> v(data.num_blocks());
    boost::to_block_range(data, v.begin());
    output_stream.write(reinterpret_cast<char*>(&v[0]), v.size() * sizeof(unsigned char));
}


void GOL_Enc::encdec(std::string in_path, std::string out_path) {
    input_stream = std::basic_ifstream<char>(in_path);
    input_size = std::filesystem::file_size(in_path);
    output_stream = std::basic_ofstream<char>(out_path, std::ios::binary );
    buffer = std::vector<char>(BLOCK_SIZE);
    while (input_size >= BLOCK_SIZE) {
        scramble_block(BLOCK_SIZE);
        input_size -= BLOCK_SIZE;
    }
    if (input_size > 0) {
        buffer = std::vector<char>(input_size);
        scramble_block(input_size);
    }
    input_stream.close();
    output_stream.close();
}

void GOL_Enc::encrypt(std::string path) {
    if (run_once) {
        std::cout << "already ran once, need to be reinitialized";
        return;
    }
    run_once = true;
    std::string out_path = path;
    out_path.replace(out_path.size()-4, 1, "-");
    encdec(path, out_path+".trc");
}

void GOL_Enc::decrypt(std::string path) {
    if (run_once) {
        std::cout << "already ran once, need to be reinitialized";
        return;
    }
    run_once = true;
    std::string out_path = path.substr(0, (path.size()-4));
    out_path = out_path.replace(out_path.size()-4, 1, ".");
    encdec(path, out_path);
}

