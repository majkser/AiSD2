#include <iostream>
#include <string>
#include "setLinked.h"

int main()
{
    setLinked A;
    A.add(1);
    A.add(3);
    A.add(4);
    A.add(2);
    A.add(-2);
    A.display();

    return 0;
}