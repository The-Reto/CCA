#include <chrono>
#include "../headers/GOL_RNG.h"
#include "../headers/GOL_Hash.h"
#include "../headers/GOL.h"
#include "../headers/C_GOL.h"

void test_RNG() {
    using namespace std::chrono;

    static const int samples = 10000;
    GOL_RNG test(35687634);
    
    std::cout << "Testing RNG Class by taking " << samples << " samples:\n";
    
    std::cout << "\tintegers: ";
    auto start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_int();
    }
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << "\tfloats: ";
    start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_float();
    }
    end = steady_clock::now();
    duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << "\tdoubles: ";
    start = steady_clock::now();
    for (int i = 0; i < samples; i++) {
        test.rand_double();
    }
    end = steady_clock::now();
    duration = end - start;
    std::cout << duration.count() << "s\n";
    
    std::cout << std::endl;
}

void test_Hash() {
    using namespace std::chrono;
    GOL_Hash txt("test.txt");
    GOL_Hash music("test.mp3");
    GOL_Hash video("test.webm");
    std::cout << "Testing Hash Class by taking the Hash of a text, a music and a video file:\n";
    
    std::cout << "\ttext file - ";
    auto start = steady_clock::now();
    txt.get_Str_Hash();
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\n";
    
    std::cout << "\tmusic file - ";
    start = steady_clock::now();
    music.get_Str_Hash();
    end = steady_clock::now();
    duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\n";
    
    std::cout << "\tvideo file - ";
    start = steady_clock::now();
    video.get_Str_Hash();
    end = steady_clock::now();
    duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\n";
    
    std::cout << std::endl;
}

void test_GOL() {
    using namespace std::chrono;
    GOL test_GOL(64,8,132463548);
    const static int generations = 10000;
    std::cout << "Testing GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_GOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\n";
    
    std::cout << std::endl;
}

void test_CGOL() {
    using namespace std::chrono;
    C_GOL test_CGOL(64,8,132463548);
    const static int generations = 10000;
    std::cout << "Testing C-GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_CGOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\n";
    
    std::cout << std::endl;
}

int main()
{
    test_GOL();
    test_CGOL();
    test_RNG();
    test_Hash();
}
