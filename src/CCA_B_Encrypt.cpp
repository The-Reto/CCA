#include <iostream>
#include "../headers/CCA_B_Enc.h"


int main(int argc, char *argv[]){ // call mode in-file Key out-file
     CCA_B_Enc encryptor(argv[3]);
     
     if ( argv[1][0] == 'e') {
          std::cout << "File to encrypt: " << argv[2] << " with key: " << argv[3]<< " and outputing to: " << argv[4] << std::endl;
     }
     else if ( argv[1][0] == 'd') {
          std::cout << "File to decrypt: " << argv[2] << " with key: " << argv[3]<< " and outputing to: " << argv[4] << std::endl;
     }
     int check; = encryptor.encrypt(argv[2], argv[4]);
     return check;
}