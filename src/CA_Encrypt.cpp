#include <iostream>
#include "../headers/GOL_Enc.h"
#include "../headers/GOL_B_Enc.h"

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
     static char* error = (char *) "-err";
     char ** itr = std::find(begin, end, option);
     if (itr != end && ++itr != end)
     {
          return *itr;
     }
     return error;
}

struct options{
     bool valid;
     std::string in_file, key, out_file, mode;
};

std::string get_output_file(std::string in_file, std::string mode) {
     if (mode[1] == 'E') { 
          std::string out_path = in_file;
          out_path.replace(out_path.size()-4, 1, "-");
          return out_path + ".trc";
     }
     else if (mode[1] == 'D' & in_file[in_file.size()-8] == '-' & in_file.substr(in_file.size()-4, 4) == ".trc") { 
          std::string out_file = in_file.substr(0, in_file.size()-8);
          std::string out_ext = in_file.substr(in_file.size()-7, 3);
          return out_file + "-DEC." + out_ext;
     }
     else {
          std::cout << "COULD NOT DEFER ORIGINAL FILE NAME, DEFAULT OUTPUT LOCATION CHOSEN." << std::endl;
          return "./CA_Encrypt_Output";
     }
}

options getOptions(int argc, char *argv[]) {
     std::string in_file = "-empty", key = "-empty", out_file = "-empty", mode = "-empty";
     
     in_file = getCmdOption(argv, argv+argc, "-f");
     if (in_file[0] == '-') {
          std::cerr << "NO INPUT FILE, ABORTING." << std::endl;
          return options(0, in_file, key, out_file, mode);
     }
     key = getCmdOption(argv, argv+argc, "-k");
     if (key[0] == '-') {
          std::cerr << "NO KEY, ABORTING." << std::endl;
          return options(0, in_file, key, out_file, mode);
     }

     mode = getCmdOption(argv, argv+argc, "-m");
     if (mode[0] == '-') {
          mode.erase(mode.begin(), mode.begin() + 1);
     }
     else if ((mode[0] != 'B' & mode[0] != 'S') | (mode[1] != 'E' & mode[1] != 'D')) {
          std::cerr << "INVALID MODE, ABORTING." << std::endl;
          return options(0, in_file, key, out_file, mode);
     }

     out_file = getCmdOption(argv, argv+argc, "-o");
     if (out_file[0] == '-') {
          out_file = get_output_file(in_file, mode);
     }

     return options(1, in_file, key, out_file, mode);
}

int main(int argc, char *argv[]){ // call -f in-file -m MODE -k Key -o out-file
     
     options myOptions = getOptions(argc, argv);
     if (!myOptions.valid) { return -1; }
     std::cout << "File to encrypt: " << myOptions.in_file << " with key: " << myOptions.key << " and outputing to: " << myOptions.out_file << std::endl;
     int check;
     if (myOptions.mode[0] == 'B') {
          GOL_B_Enc encryptor(myOptions.key);
          if (myOptions.mode[1] == 'E') {
               check = encryptor.encrypt(myOptions.in_file, myOptions.out_file);
          }
          if (myOptions.mode[1] == 'D') {
               check = encryptor.decrypt(myOptions.in_file, myOptions.out_file);
          }
     }
     else if (myOptions.mode[0] == 'S') {
          GOL_Enc encryptor(myOptions.key);
          check = encryptor.encrypt(myOptions.in_file, myOptions.out_file);
     }

     return check;
}