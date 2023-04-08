#include <chrono>
#include "../headers/C_GOL.h"

void test_GOL() {
    C_GOL test(32,32,0xefecafe1);
    system("clear");
    
    std::cout << "C-GOL Simulation \t Initial configuration" << "\n";
    test.print();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("clear");
    
    for (int i = 1; i<200; ++i) {
        std::cout << "C-GOL Simulation \t Generation: " << i << "\n";
        test.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
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
