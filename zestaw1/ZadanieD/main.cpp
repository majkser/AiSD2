#include <iostream>
#include <string>
#include "dictionarySimple.h"

int main()
{

    dictionarySimple A(10);

    A.add("Ala");
    A.add("ma");
    A.add("kota");
    A.remove("ma");

    A.display();

    std::cout << "Contains 'Ala': " << std::boolalpha << A.contains("Ala") << std::endl;
    std::cout << "Contains 'ma': " << std::boolalpha << A.contains("ma") << std::endl;
}