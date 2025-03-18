#include <iostream>
#include <string>
#include "setSimple.h"
#include "setOperations.h"
#include <random>
#include <chrono>
#include <fstream>

void measureTimeComplexity()
{
    std::ofstream outfile("time_complexity_results.txt");

    for (int n = 10; n <= 1000; n += 10)
    {
        setSimple A(n, "A");
        setSimple B(n, "B");

        for (int i = 0; i < n; ++i)
        {
            A.add(rand());
            B.add(rand());
        }

        auto start = std::chrono::high_resolution_clock::now();
        setSimple C = setUnion(A, B);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        outfile << n << " " << duration.count() << std::endl;
    }

    outfile.close();
}

int main()
{

    measureTimeComplexity();
    setSimple A(10, "A");
    setSimple B(20, "B");

    std::cout << std::boolalpha;
    A.add(1);
    A.add(2);
    A.add(3);
    A.add(12);
    A.add(13);
    A.remove(2);

    B.add(3);
    B.add(4);
    B.add(1);
    B.add(5);

    setSimple C = setUnion(A, B);
    setSimple D = setIntersection(A, B);
    setSimple E = setDiff(A, B);
    std::cout << "A: ";
    A.display();
    std::cout << "B: ";
    B.display();
    C.display();
    D.display();
    E.display();

    setSimple F(30, "F");
    F.add(1);
    setSimple G(30, "G");
    G.add(1);
    G.add(2);
    std::cout << setIdentity(F, G);
    return 0;
}