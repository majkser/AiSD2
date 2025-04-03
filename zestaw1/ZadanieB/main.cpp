#include <iostream>
#include <string>
#include "setLinked.h"
#include "setOperations.h"

int main()
{
    setLinked A;
    A.add(1);
    A.add(3);
    A.add(4);
    A.add(2);
    A.add(-2);
    A.remove(3);
    A.display();
    // std::cout << A.contains(3) << std::endl;
    // std::cout << A.contains(-2) << std::endl;

    setLinked B;
    B.add(3);
    B.add(4);
    B.add(0);
    B.add(2);
    B.display();

    setLinked C = setUnion(A, B);
    C.display();

    setLinked D = setIntersection(A, B);
    D.display();

    setLinked E = setDiff(A, B);
    E.display();

    setLinked F;
    F.add(3);
    F.add(4);
    F.add(0);
    F.add(2);

    bool areEqual = setIdentity(A, B);
    std::cout << std::boolalpha << areEqual << std::endl;

    bool areEqual2 = setIdentity(F, B);
    std::cout << std::boolalpha << areEqual2 << std::endl;

    return 0;
}