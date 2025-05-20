#include <iostream>
#include <string>
#include "priorityQueueBinary.h"
#include <fstream>

void measureTimeComplexity()
{
    std::ofstream outfile("time_complexity_getAndRemove_priorityQueueBinary.txt");

    for (int n = 10; n <= 800; n += 10)
    {
        double totalGetAndRemove = 0;

        priorityQueueBinary queue(n);

        // First, create a queue with n elements
        for (int i = 0; i < n; i++)
        {
            queue.insert(rand() % n + 1);
        }

        const int trials = n;
        for (int k = 0; k < trials; k++)
        {
            // Get and remove operation
            auto startGetAndRemove = std::chrono::high_resolution_clock::now();
            queue.deleteMin();
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

    // priorityQueueBinary queue = priorityQueueBinary(10);
    // queue.insert(2);
    // queue.insert(19);
    // queue.insert(21);
    // queue.insert(9);
    // queue.insert(11);

    // queue.display();
    // std::cout << queue.deleteMin() << std::endl;
    // queue.display();

    return 0;
}