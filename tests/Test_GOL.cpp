#include <chrono>
#include "../headers/GOL.h"

void test_GOL() {
    GOL test(64,64,0xefecafe1);
    system("clear");
    
    std::cout << "GOL Simulation \t Initial configuration" << "\n";
    test.print();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("clear");
    
    for (int i = 0; i<400; ++i) {
        std::cout << "GOL Simulation \t Generation: " << i+1 << "\n";
        test.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
        test.step();
        system("clear");
    }
    
    std::cout << std::endl;
    system("clear");
}

int main()
{
    test_GOL();

}
