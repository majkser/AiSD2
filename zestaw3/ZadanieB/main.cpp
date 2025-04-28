#include <iostream>
#include <string>
#include "priorityQueueBinary.h"

int main()
{
    priorityQueueBinary queue = priorityQueueBinary(10);
    queue.insert(2);
    queue.insert(19);
    queue.insert(21);
    queue.insert(9);
    queue.insert(11);

    queue.display();
    std::cout << queue.deleteMin() << std::endl;
    queue.display();

    return 0;
}