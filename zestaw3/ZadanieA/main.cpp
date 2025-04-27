#include <iostream>
#include <string>
#include "priorityQueue.h"

int main()
{
    priorityQueue queue = priorityQueue();
    queue.add(1);
    queue.add(2);
    queue.add(8);
    queue.add(3);
    queue.add(5);

    queue.display();

    std::cout << queue.getAndRemove() << std::endl;
    std::cout << queue.getAndRemove() << std::endl;

    queue.display();

    return 0;
}