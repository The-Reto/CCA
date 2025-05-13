#include "../include/CCA_Wiper.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
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


int main(int argc, char *argv[]){
    std::string seed = argv[argc-1];
    CCA_Wiper::wipe(argv[argc-1], argv[argc-1] + currentDateTime());
}