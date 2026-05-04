#include <iostream>
#include "include/FIFO.hpp"

using namespace std;

int main()
{
    FIFO cache(3);
    cout<<cache.get_hits()<<endl;
    return 0;
}