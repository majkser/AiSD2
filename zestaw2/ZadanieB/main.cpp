#include <iostream>
#include <string>
#include "setHashed.h"

int main()
{
    setHashed set = setHashed(11);
    set.add(11);
    set.add(22);

    set.add(7);
    set.add(18);

    set.remove(18);

    // std::cout << set.contains(11);
    // std::cout << set.contains(7);
    // std::cout << set.contains(44);

    setHashed set2 = setHashed(11);
    set2.add(11);
    set2.add(22);
    set2.add(33);

    set2.add(4);

    setHashed set3 = setUnion(set, set2);
    setHashed set4 = setIntersection(set, set2);
    setHashed set5 = setDiff(set, set2);
    setHashed set6 = setDiff(set, set2);

    std::cout << "SetIDE: " << setIdentity(set5, set6) << std::endl;

    // set.display();
    // set3.display();
    set5.display();
}
