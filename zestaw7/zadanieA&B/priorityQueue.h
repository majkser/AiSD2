#ifndef priorityQueue_h
#define priorityQueue_h

#include <iostream>
#include <utility>

struct PairNode
{
    int vertex;
    int distance;
    PairNode *next;

    PairNode(int v, int d) : vertex(v), distance(d), next(nullptr) {}
};

class priorityQueue
{
private:
    PairNode *head;

public:
    priorityQueue();
    ~priorityQueue();

    void add(int vertex, int distance);

    std::pair<int, int> deleteMin();

    bool isEmpty() const { return head == nullptr; }
    void display();
};

priorityQueue::priorityQueue() : head(nullptr)
{
}

priorityQueue::~priorityQueue()
{
    while (head)
    {
        PairNode *temp = head;
        head = head->next;
        delete temp;
    }
}

void priorityQueue::add(int vertex, int distance)
{
    PairNode *newNode = new PairNode(vertex, distance);

    // Empty list or new node has lower distance than head
    if (head == nullptr || distance < head->distance)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Insert in sorted order based on distance
    PairNode *current = head;
    while (current->next && current->next->distance <= distance)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

std::pair<int, int> priorityQueue::deleteMin()
{
    if (head == nullptr)
    {
        return {-1, -1}; // Empty queue
    }

    PairNode *temp = head;
    std::pair<int, int> result = {temp->vertex, temp->distance};
    head = head->next;
    delete temp;

    return result;
}

void priorityQueue::display()
{
    PairNode *current = head;
    std::cout << "Priority Queue: ";
    while (current)
    {
        std::cout << "(" << current->vertex << "," << current->distance << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif // priorityQueue_h