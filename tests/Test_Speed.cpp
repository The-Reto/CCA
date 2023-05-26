#include <chrono>
#include <ratio>
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
    GOL_Hash txt("test_data/test.txt");
    GOL_Hash music("test_data/test.mp3");
    GOL_Hash video("test_data/test.webm");
    std::cout << "Testing Hash Class by taking the Hash of a text, a music and a video file:\n";
    
    std::cout << "\ttext file (" << 10'204 << " Bytes): ";
    auto start = steady_clock::now();
    txt.get_Str_Hash();
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::chrono::microseconds durationMS = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() / 10'204.0 << "ms/byte, "<< 512*durationMS.count() / 10'204.0 <<"ms/generation)\n";
    
    std::cout << "\tvideo file (" << 2'391'888 << " Bytes): ";
    start = steady_clock::now();
    video.get_Str_Hash();
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t(" << durationMS.count() /  2'391'888.0  << "ms/byte, "<< 512*durationMS.count()/  2'391'888.0 <<"ms/generation)\n";
    
    std::cout << "\tmusic file (" << 41'508'864 << " Bytes): ";
    start = steady_clock::now();
    music.get_Str_Hash();
    end = steady_clock::now();
    duration = end - start;
    durationMS = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    std::cout << "\ttime: " << duration.count() << "s \t\t(" << durationMS.count() / 41'508'864.0  << "ms/byte, "<< 512*durationMS.count() / 41'508'864.0 <<"ms/generation)\n";
    
    std::cout << std::endl;
}

void test_GOL() {
    using namespace std::chrono;
    GOL test_GOL(64,64,0xefecafe1);
    const static int generations = 10000;
    std::cout << "Testing GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_GOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    test_GOL.print();
    std::cout << "\ttime: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / generations << "ms/generation)\n";
    std::cout << std::endl;
}

void test_CGOL() {
    using namespace std::chrono;
    C_GOL test_CGOL(64,64,0xefecafe1);
    const static int generations = 10000;
    std::cout << "Testing C-GOL Class by taking running a random setting for " << generations << " generations.\n";
    auto start = steady_clock::now();
    test_CGOL.steps(generations);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    std::cout << "\ttime: " << duration.count() << "s\t(" << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / generations << "ms/generation)\n";
    
    std::cout << std::endl;
}

int main()
{
    test_GOL();
    test_CGOL();
    test_RNG();
    test_Hash();
}
