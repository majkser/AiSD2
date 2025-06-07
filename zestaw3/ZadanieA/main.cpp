#include <iostream>
#include <string>
#include "priorityQueue.h"
#include <fstream>
#include <chrono>

void measureTimeComplexity()
{
    std::ofstream outfile("time_complexity_getAndRemove_priorityQueue.txt");

    for (int n = 10; n <= 800; n += 10)
    {
        double totalGetAndRemove = 0;

        priorityQueue queue;

        // First, create a queue with n elements
        for (int i = 0; i < n; ++i)
        {
            queue.add(rand() % n + 1);
        }

        const int trials = n;
        for (int k = 0; k < trials; k++)
        {
            // Get and remove operation
            auto startGetAndRemove = std::chrono::high_resolution_clock::now();
            queue.getAndRemove();
            auto endGetAndRemove = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> durationGetAndRemove = endGetAndRemove - startGetAndRemove;
            totalGetAndRemove += durationGetAndRemove.count();
        }
        double avgGetAndRemove = totalGetAndRemove / trials;
        outfile << n << " " << avgGetAndRemove << std::endl;
    }
    outfile.close();
}

int main()
{
    measureTimeComplexity();

    // priorityQueue queue = priorityQueue();

    // queue.add(2);
    // queue.add(8);
    // queue.add(3);
    // queue.add(5);
    // queue.add(1);

    // queue.display();

    // std::cout << queue.getAndRemove() << std::endl;
    // std::cout << queue.getAndRemove() << std::endl;

    // queue.display();

    return 0;
}