#ifndef setHashed_h
#define setHashed_h

#include <iostream>
#include <string>
#include "../../zestaw1/ZadanieB/setLinked.h"

class setHashed
{
private:
    /* data */
public:
    setHashed(int size);
    ~setHashed();

    setLinked *elements;
    int capacity;
    int count;
    int hashFunction(int value);
    void add(int value);
    void remove(int value);
    bool contains(int value);
    void display();
};

setHashed::setHashed(int size)
{
    capacity = size;
    elements = new setLinked[capacity];
}

setHashed::~setHashed()
{
}

int setHashed::hashFunction(int value)
{
    return value % capacity;
}

void setHashed::add(int value)
{
    elements[hashFunction(value)].add(value);
}

void setHashed::remove(int value)
{
    elements[hashFunction(value)].remove(value);
}

bool setHashed::contains(int value)
{
    return elements[hashFunction(value)].contains(value);
}

void setHashed::display()
{
    for (int i = 0; i < capacity; i++)
    {
        std::cout << "Hash " << i << ": ";
        elements[i].display();
    }
    std::cout << std::endl;
}

setHashed setUnion(setHashed A, setHashed B)
{

    setHashed result = setHashed(A.capacity);

    for (int i = 0; i < A.capacity; i++)
    {
        Node *current = A.elements[i].head;
        while (current != nullptr)
        {
            result.add(current->value);
            current = current->next;
        }
    }

    for (int i = 0; i < B.capacity; i++)
    {
        Node *current = B.elements[i].head;
        while (current != nullptr)
        {
            if (!result.contains(current->value))
            {
                result.add(current->value);
            }
            current = current->next;
        }
    }
    return result;
}

setHashed setIntersection(setHashed A, setHashed B)
{
    setHashed result = setHashed(A.capacity);

    for (int i = 0; i < A.capacity; i++)
    {
        Node *current = A.elements[i].head;
        while (current != nullptr)
        {
            if (B.contains(current->value))
            {
                result.add(current->value);
            }
            current = current->next;
        }
    }

    return result;
}

setHashed setDiff(setHashed A, setHashed B)
{
    setHashed result = setHashed(A.capacity);

    for (int i = 0; i < A.capacity; i++)
    {
        Node *current = A.elements[i].head;
        while (current != nullptr)
        {
            if (!B.contains(current->value))
            {
                result.add(current->value);
            }
            current = current->next;
        }
    }
    return result;
}
bool setIdentity(setHashed A, setHashed B)
{
    for (int i = 0; i < A.capacity; i++)
    {
        Node *currentA = A.elements[i].head;
        Node *currentB = B.elements[i].head;
        while (currentA != nullptr && currentB != nullptr)
        {
            if (currentB == nullptr || currentA->value != currentB->value)
            {
                return false;
            }
            currentA = currentA->next;
            currentB = currentB->next;
        }

        if (currentA != nullptr || currentB != nullptr)
        {
            return false;
        }
    }

    return true;
}

#endif // setHashed_h