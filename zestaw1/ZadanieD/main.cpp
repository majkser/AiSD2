#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include "dictionarySimple.h"

void measureTimeComplexity()
{
    std::ofstream outfileAdd("time_complexity_results_Add_dictionarySimple.txt");
    std::ofstream outfileRemove("time_complexity_results_Remove_dictionarySimple.txt");
    std::ofstream outfileContains("time_complexity_results_Contains_dictionarySimple.txt");

    for (int n = 10; n <= 500; n += 10)
    {
        double totalAdd = 0;
        double totalRemove = 0;
        double totalContains = 0;

        // Generate test strings
        std::vector<std::string> allStrings;
        for (int i = 0; i < n * 2; i++)
        {
            std::string randomStr;
            for (int j = 0; j < 8; j++)
            {
                randomStr += 'a' + (rand() % 26);
            }
            allStrings.push_back(randomStr);
        }

        std::vector<std::string> testStrings;
        for (int i = 0; i < 200; i++)
        {
            testStrings.push_back(allStrings[n + i]);
        }

        const int trials = 200;
        for (int k = 0; k < trials; k++)
        {
            // Measure Add operation
            {
                dictionarySimple dict(n);
                for (int i = 0; i < n - 1; i++)
                {
                    dict.add(allStrings[i]);
                }
                std::string valueToAdd = testStrings[k % testStrings.size()];
                auto startAdd = std::chrono::high_resolution_clock::now();
                dict.add(valueToAdd);
                auto endAdd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationAdd = endAdd - startAdd;
                totalAdd += durationAdd.count();
            }

            // Measure Contains operation
            {
                dictionarySimple dict(n);
                for (int i = 0; i < n; i++)
                {
                    dict.add(allStrings[i]);
                }
                std::string valueToFind = (k % 2 == 0) ? allStrings[k % n] : testStrings[k % 200];
                auto startContains = std::chrono::high_resolution_clock::now();
                dict.contains(valueToFind);
                auto endContains = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationContains = endContains - startContains;
                totalContains += durationContains.count();
            }

            // Measure Remove operation
            {
                dictionarySimple dict(n);
                for (int i = 0; i < n; i++)
                {
                    dict.add(allStrings[i]);
                }
                std::string valueToRemove = allStrings[k % n];
                auto startRemove = std::chrono::high_resolution_clock::now();
                dict.remove(valueToRemove);
                auto endRemove = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> durationRemove = endRemove - startRemove;
                totalRemove += durationRemove.count();
            }
        }

        double avgAdd = totalAdd / trials;
        double avgRemove = totalRemove / trials;
        double avgContains = totalContains / trials;

        outfileAdd << n << " " << avgAdd << std::endl;
        outfileRemove << n << " " << avgRemove << std::endl;
        outfileContains << n << " " << avgContains << std::endl;
    }

    outfileAdd.close();
    outfileRemove.close();
    outfileContains.close();
}

int main()
{
    // dictionarySimple A(10);

    // A.add("Ala");
    // A.add("ma");
    // A.add("kota");
    // A.remove("ma");

    // A.display();

    // std::cout << "Contains 'Ala': " << std::boolalpha << A.contains("Ala") << std::endl;
    // std::cout << "Contains 'ma': " << std::boolalpha << A.contains("ma") << std::endl;

    measureTimeComplexity();

    return 0;
}