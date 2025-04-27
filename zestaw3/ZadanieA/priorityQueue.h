#ifndef priorityQueue_h
#define priorityQueue_h

#include <iostream>
#include "../../zestaw1/ZadanieB/setLinked.h"

class priorityQueue
{
private:
public:
    priorityQueue();
    ~priorityQueue();

    setLinked elements;

    void add(int value);
    int getAndRemove();
    void display();
};

priorityQueue::priorityQueue()
{
}
priorityQueue::~priorityQueue()
{
}

void priorityQueue::add(int value)
{
    elements.add(value);
    // priorytetem jest wartosc - setLinked jest posortowany rosnaco
    // wiec poprotu dodajemy a setLinked sam zadba o posortowanie
}

int priorityQueue::getAndRemove()
{
    if (elements.head == nullptr)
    {
        return -1;
    }

    Node *head = elements.head;
    int value = head->value;
    elements.head = elements.head->next;
    delete head;

    return value;
}

void priorityQueue::display()
{
    elements.display();
}

#endif // priorityQueue_h