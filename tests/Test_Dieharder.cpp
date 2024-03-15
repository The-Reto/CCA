#include "../headers/GOL_Keygen.h"

int main()
{
    GOL_Keygen test_a("b");
    int res = 0;
    while (true) {
         res = write(1,&test_a.get_streched_key()[0],512);
    }
}