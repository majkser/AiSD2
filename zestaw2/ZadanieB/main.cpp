#include <iostream>
#include <string>
#include "setHashed.h"
#include <fstream>

void measureTimeComplexity()
{
    std::ofstream outfileUnion("time_complexity_results_union_setHashed.txt");
    std::ofstream outfileIntersection("time_complexity_results_Intersection_setHashed.txt");
    std::ofstream outfileDiff("time_complexity_results_Diff_setHashed.txt");
    std::ofstream outfileIdentity("time_complexity_results_Identity_setHashed.txt");
    std::ofstream outfileAdd("time_complexity_results_Add_setHashed.txt");
    std::ofstream outfileRemove("time_complexity_results_Remove_setHashed.txt");
    std::ofstream outfileContains("time_complexity_results_Contains_setHashed.txt");

    for (int n = 10; n <= 800; n += 10)
    {
        double totalUnion = 0;
        double totalIntersection = 0;
        double totalDiff = 0;
        double totalIdentity = 0;
        double totalAdd = 0;
        double totalRemove = 0;
        double totalContains = 0;

        setHashed A(n);
        setHashed B(n);

        // First, create sets with n elements
        for (int i = 0; i < n; ++i)
        {
            A.add(rand() % n + 1);
            B.add(rand() % n + 1);
        }

        // Prepare test values for add/remove/contains
        std::vector<int> testValues;
        for (int i = 0; i < 100; i++)
        {
            testValues.push_back(rand() % (n * 2) + 1); // Values that may or may not be in the sets
        }

        const int trials = 200;
        for (int k = 0; k < trials; k++)
        {
            // Union operation
            auto startUnion = std::chrono::high_resolution_clock::now();
            setHashed C = setUnion(A, B);
            auto endUnion = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationUnion = endUnion - startUnion;
            totalUnion += durationUnion.count();

            // Intersection operation
            auto startIntersection = std::chrono::high_resolution_clock::now();
            setHashed D = setIntersection(A, B);
            auto endIntersection = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIntersection = endIntersection - startIntersection;
            totalIntersection += durationIntersection.count();

            // Diff operation
            auto startDiff = std::chrono::high_resolution_clock::now();
            setHashed E = setDiff(A, B);
            auto endDiff = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationDiff = endDiff - startDiff;
            totalDiff += durationDiff.count();

            // Identity operation
            auto startIdentity = std::chrono::high_resolution_clock::now();
            bool areEqual = setIdentity(A, B);
            auto endIdentity = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationIdentity = endIdentity - startIdentity;
            totalIdentity += durationIdentity.count();

            // Add operation
            int valueToAdd = testValues[k % testValues.size()];
            auto startAdd = std::chrono::high_resolution_clock::now();
            A.add(valueToAdd);
            auto endAdd = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationAdd = endAdd - startAdd;
            totalAdd += durationAdd.count();

            // Contains operation
            int valueToFind = testValues[k % testValues.size()];
            auto startContains = std::chrono::high_resolution_clock::now();
            bool contains = A.contains(valueToFind);
            auto endContains = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationContains = endContains - startContains;
            totalContains += durationContains.count();

            // Remove operation
            int valueToRemove = testValues[k % testValues.size()];
            auto startRemove = std::chrono::high_resolution_clock::now();
            A.remove(valueToRemove);
            auto endRemove = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationRemove = endRemove - startRemove;
            totalRemove += durationRemove.count();
        }
        double avgUnion = totalUnion / trials;
        double avgIntersection = totalIntersection / trials;
        double avgDiff = totalDiff / trials;
        double avgIdentity = totalIdentity / trials;
        double avgAdd = totalAdd / trials;
        double avgRemove = totalRemove / trials;
        double avgContains = totalContains / trials;

        outfileUnion << n << " " << avgUnion << std::endl;
        outfileIntersection << n << " " << avgIntersection << std::endl;
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
    // measureTimeComplexity();

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

    set.display();
    // set3.display();
    // set5.display();
}
