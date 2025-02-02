#include "../../headers/CCA_Archive.h"
#include <fstream>
#include <filesystem>

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

CCA_Archive::CCA_Archive(std::string _key): key(_key) {
    std::istringstream stream(currentDateTime());
    CCA_Hash hash(stream, 19);
    salt = hash.get_Str_Hash();
}

void CCA_Archive::pack(std::string in_path, std::string out_path) {
        if (!std::filesystem::exists(in_path) || !std::filesystem::is_directory(in_path)) {
            std::cerr << "Error: Directory does not exist or is not a directory." << std::endl;
            return;
        }
        CCA_S_Enc encryptor(key + salt);
        std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path, std::ios::binary );
        output_stream << salt << ";";
        // Iterate over directory entries
        for (const auto& entry : std::filesystem::recursive_directory_iterator(in_path)) {
            if (std::filesystem::is_regular_file(entry.path())) { // Check if it's a file
                std::string f_name = entry.path().string();
                unsigned long f_size = std::filesystem::file_size(f_name), fn_size = f_name.length();
                output_stream << fn_size << ";" << f_size << ";";
                std::stringstream str_str(f_name);
                encryptor.encdec(&str_str, fn_size, &output_stream);
                std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(f_name);
                encryptor.encdec(&input_stream, f_size, &output_stream);
                input_stream.close();
            }
        }
        output_stream.close();
}

void CCA_Archive::unpack(std::string in_path, std::string out_path) {
        std::basic_ifstream<char> input_stream = std::basic_ifstream<char>(in_path);
        std::string f_salt;
        std::getline(input_stream, f_salt, ';');
        CCA_S_Enc encryptor(key + f_salt);

        std::string f_size_str, fn_size_str, f_name;
        int f_size, fn_size;
        while (std::getline(input_stream, fn_size_str, ';') && std::getline(input_stream, f_size_str, ';'))
        {
            std::cout << "loop" << std::endl;
            std::stringstream n_str_f_size(f_size_str), n_str_fn_size(fn_size_str), fn_stream;
            n_str_f_size >> f_size;
            n_str_fn_size >> fn_size;

            encryptor.encdec(&input_stream, fn_size, &fn_stream);
            f_name = fn_stream.str();
            std::cout << f_name << std::endl;
            std::cout << fn_size_str << std::endl;
            std::cout << f_size_str << std::endl;
            std::filesystem::create_directories(std::filesystem::path(out_path + f_name).parent_path());
            std::basic_ofstream<char> output_stream = std::basic_ofstream<char>(out_path + f_name, std::ios::binary );

            encryptor.encdec(&input_stream, f_size, &output_stream);

            output_stream.close();
        }
        
        input_stream.close();
}