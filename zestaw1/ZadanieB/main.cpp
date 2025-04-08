#include <iostream>
#include <string>
#include "setLinked.h"
#include "setOperations.h"
#include <random>
#include <chrono>
#include <fstream>

void measureTimeComplexity()
{
    std::ofstream outfileUnion("time_complexity_results_union_setLinked.txt");
    std::ofstream outfileIntersection("time_complexity_results_Intersection_setLinked.txt");
    std::ofstream outfileDiff("time_complexity_results_Diff_setLinked.txt");
    std::ofstream outfileIdentity("time_complexity_results_Identity_setLinked.txt");
    std::ofstream outfileAdd("time_complexity_results_Add_setLinked.txt");
    std::ofstream outfileRemove("time_complexity_results_Remove_setLinked.txt");
    std::ofstream outfileContains("time_complexity_results_Contains_setLinked.txt");

    for (int n = 10; n <= 800; n += 10)
    {
        double totalUnion = 0;
        double totalIntersection = 0;
        double totalDiff = 0;
        double totalIdentity = 0;
        double totalAdd = 0;
        double totalRemove = 0;
        double totalContains = 0;

        setLinked A;
        setLinked B;

        // First, create sets with n elements
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
            // Union operation
            auto startUnion = std::chrono::high_resolution_clock::now();
            setLinked C = setUnion(A, B);
            auto endUnion = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationUnion = endUnion - startUnion;
            totalUnion += durationUnion.count();

            // Intersection operation
            auto startIntersection = std::chrono::high_resolution_clock::now();
            setLinked D = setIntersection(A, B);
            auto endIntersection = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIntersection = endIntersection - startIntersection;
            totalIntersection += durationIntersection.count();

            // Diff operation
            auto startDiff = std::chrono::high_resolution_clock::now();
            setLinked E = setDiff(A, B);
            auto endDiff = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationDiff = endDiff - startDiff;
            totalDiff += durationDiff.count();

            // Identity operation
            auto startIdentity = std::chrono::high_resolution_clock::now();
            bool identity = setIdentity(A, B);
            auto endIdentity = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIdentity = endIdentity - startIdentity;
            totalIdentity += durationIdentity.count();

            // Add operation (to an existing set with n elements)
            int valueToAdd = testValues[k % testValues.size()];
            setLinked testAdd = A; // Copy the set with n elements
            auto startAdd = std::chrono::high_resolution_clock::now();
            testAdd.add(valueToAdd);
            auto endAdd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationAdd = endAdd - startAdd;
            totalAdd += durationAdd.count();

            // Remove operation (from an existing set with n elements)
            int valueToRemove = testValues[k % testValues.size()];
            setLinked testRemove = A; // Copy the set with n elements
            // First ensure the element exists
            testRemove.add(valueToRemove);
            auto startRemove = std::chrono::high_resolution_clock::now();
            testRemove.remove(valueToRemove);
            auto endRemove = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationRemove = endRemove - startRemove;
            totalRemove += durationRemove.count();

            // Contains operation (in an existing set with n elements)
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
        outfileUnion << n << " " << avgUnion << std::endl;
        outfileIntersection << n << " " << avgIntersection << std::endl;
        outfileDiff << n << " " << avgDiff << std::endl;
        outfileIdentity << n << " " << avgIdentity << std::endl;
        outfileAdd << n << " " << avgAdd << std::endl;
        outfileRemove << n << " " << avgRemove << std::endl;
        outfileContains << n << " " << avgContains << std::endl;
    }

    // Close all file streams
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
    // setLinked A;
    // A.add(1);
    // A.add(3);
    // A.add(4);
    // A.add(2);
    // A.add(-2);
    // A.remove(3);
    // A.display();
    // // std::cout << A.contains(3) << std::endl;
    // // std::cout << A.contains(-2) << std::endl;

    // setLinked B;
    // B.add(3);
    // B.add(4);
    // B.add(0);
    // B.add(2);
    // B.display();

    // setLinked C = setUnion(A, B);
    // C.display();

    // setLinked D = setIntersection(A, B);
    // D.display();

    // setLinked E = setDiff(A, B);
    // E.display();

    // setLinked F;
    // F.add(3);
    // F.add(4);
    // F.add(0);
    // F.add(2);

    // bool areEqual = setIdentity(A, B);
    // std::cout << std::boolalpha << areEqual << std::endl;

    // bool areEqual2 = setIdentity(F, B);
    // std::cout << std::boolalpha << areEqual2 << std::endl;

    measureTimeComplexity();

    return 0;
}