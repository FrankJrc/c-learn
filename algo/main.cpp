#include <iostream>
#include <memory>
#include "binary_search_demo.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    //RAII
    std::unique_ptr<demo> d = std::make_unique<binary_search_demo>();
    d->run();

    return 0;
}
