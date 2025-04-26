#include <iostream>
#include <string>
#include "setSimple.h"
#include "setOperations.h"
#include <random>
#include <chrono>
#include <fstream>

void measureTimeComplexity()
{
    std::ofstream outfileUnion("time_complexity_results_union_setSimple.txt");
    std::ofstream outfileIntersection("time_complexity_results_Intersection_setSimple.txt");
    std::ofstream outfileDiff("time_complexity_results_Diff_setSimple.txt");
    std::ofstream outfileIdentity("time_complexity_results_Identity_setSimple.txt");
    std::ofstream outfileAdd("time_complexity_results_Add_setSimple.txt");
    std::ofstream outfileRemove("time_complexity_results_Remove_setSimple.txt");
    std::ofstream outfileContains("time_complexity_results_Contains_setSimple.txt");

    for (int n = 10; n <= 800; n += 10)
    {
        double totalUnion = 0;
        double totalIntersection = 0;
        double totalDiff = 0;
        double totalIdentity = 0;
        double totalAdd = 0;
        double totalRemove = 0;
        double totalContains = 0;

        setSimple A(n, "A");
        setSimple B(n, "B");

        for (int i = 0; i < n; ++i)
        {
            A.add(rand() % n + 1);
            B.add(rand() % n + 1);
        }

        // Prepare test values for add/remove/contains
        std::vector<int> testValues;
        for (int i = 0; i < 200; i++)
        {
            testValues.push_back(rand() % (n * 2) + 1); // Values that may or may not be in the sets
        }

        const int trials = 200;
        for (int k = 0; k < trials; k++)
        {
            auto startUnion = std::chrono::high_resolution_clock::now();
            setSimple C = setUnion(A, B);
            auto endUnion = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationUnion = endUnion - startUnion;
            totalUnion += durationUnion.count();

            auto startIntersection = std::chrono::high_resolution_clock::now();
            setSimple D = setIntersection(A, B);
            auto endIntersection = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIntersection = endIntersection - startIntersection;
            totalIntersection += durationIntersection.count();

            auto startDiff = std::chrono::high_resolution_clock::now();
            setSimple E = setDiff(A, B);
            auto endDiff = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationDiff = endDiff - startDiff;
            totalDiff += durationDiff.count();

            auto startIdentity = std::chrono::high_resolution_clock::now();
            bool identity = setIdentity(A, B);
            auto endIdentity = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIdentity = endIdentity - startIdentity;
            totalIdentity += durationIdentity.count();

            // Add operation (to an existing set)
            int valueToAdd = testValues[k % testValues.size()];
            setSimple testAdd(n, "testAdd"); // Create new set with capacity n
            for (int i = 0; i < n - 1; i++)
            { // Add n-1 elements first
                testAdd.add(rand() % n + 1);
            }
            auto startAdd = std::chrono::high_resolution_clock::now();
            testAdd.add(valueToAdd);
            auto endAdd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationAdd = endAdd - startAdd;
            totalAdd += durationAdd.count();

            // Remove operation
            setSimple testRemove(n, "testRemove");
            for (int i = 0; i < n; i++)
            {
                testRemove.add(i + 1); // Add sequential numbers to make sure they exist
            }
            int valueToRemove = (k % n) + 1; // Ensure the value exists in the set
            auto startRemove = std::chrono::high_resolution_clock::now();
            testRemove.remove(valueToRemove);
            auto endRemove = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationRemove = endRemove - startRemove;
            totalRemove += durationRemove.count();

            // Contains operation
            int valueToFind = testValues[k % testValues.size()];
            auto startContains = std::chrono::high_resolution_clock::now();
            A.contains(valueToFind);
            auto endContains = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationContains = endContains - startContains;
            totalContains += durationContains.count();
        }

        // Calculate averages
        double avgUnion = totalUnion / trials;
        double avgIntersection = totalIntersection / trials;
        double avgDiff = totalDiff / trials;
        double avgIdentity = totalIdentity / trials;
        double avgAdd = totalAdd / trials;
        double avgRemove = totalRemove / trials;
        double avgContains = totalContains / trials;

        // Write average values to files
        outfileIntersection << n << " " << avgIntersection << std::endl;
        outfileUnion << n << " " << avgUnion << std::endl;
        outfileDiff << n << " " << avgDiff << std::endl;
        outfileIdentity << n << " " << avgIdentity << std::endl;
        outfileAdd << n << " " << avgAdd << std::endl;
        outfileRemove << n << " " << avgRemove << std::endl;
        outfileContains << n << " " << avgContains << std::endl;
    }
    outfileUnion.close();
    outfileIntersection.close();
    outfileDiff.close();
    outfileIdentity.close();
    outfileAdd.close();
    outfileRemove.close();
    outfileContains.close();
}

int main()
{
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
    std::cout << "A union B: ";
    C.display();
    std::cout << "A intersection B: ";
    D.display();
    std::cout << "A diff B: ";
    E.display();

    std::cout << "A === B: " << setIdentity(A, B);

    // measureTimeComplexity();
    return 0;
}