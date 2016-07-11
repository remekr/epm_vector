#include <iostream>
#include "vector.h"

using namespace epam;
int main()

{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    std::cout << "size: " << v.getSize() << "\n";
    std::cout << "capacity: " << v.getCapacity() << "\n";

    v.resize(0);
    std::cout << "size: " << v.getSize() << "\n";
    std::cout << "capacity: " << v.getCapacity() << "\n";
}
