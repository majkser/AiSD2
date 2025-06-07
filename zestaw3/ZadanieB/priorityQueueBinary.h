#include <iostream>

class priorityQueueBinary
{
private:
public:
    priorityQueueBinary(int size);
    ~priorityQueueBinary();

    int *elements;
    int capacity;
    int count;

    void percolateUp();
    void percolateDown();
    int getMinChild(int index);

    void insert(int value);
    int deleteMin();

    bool isEmpty() { return count == 0; }

    void display();
};

priorityQueueBinary::priorityQueueBinary(int size)
{
    capacity = size;
    elements = new int[capacity];
    elements[0] = 0;
    count = 0;
}

priorityQueueBinary::~priorityQueueBinary()
{
}

void priorityQueueBinary::percolateUp()
{
    int index = count;
    while (int(index / 2) > 0)
    {
        if (elements[index] < elements[int(index / 2)])
        {
            std::swap(elements[index], elements[int(index / 2)]);
            index = int(index / 2);
        }
        else
        {
            break;
        }
    }
}

void priorityQueueBinary::insert(int value)
{
    ++count;
    elements[count] = value;
    percolateUp();
}

int priorityQueueBinary::getMinChild(int index)
{
    if (index * 2 + 1 > count)
    {
        return index * 2;
    }
    else if (elements[index * 2] < elements[index * 2 + 1])
    {
        return index * 2;
    }
    else
    {
        return index * 2 + 1;
    }
}

void priorityQueueBinary::percolateDown()
{
    int index = 1;
    while (index * 2 <= count)
    {
        int minChild = getMinChild(index);
        if (elements[index] > elements[minChild])
        {
            std::swap(elements[index], elements[minChild]);
            index = minChild;
        }
        else
        {
            break;
        }
    }
}

int priorityQueueBinary::deleteMin()
{
    int valueToReturn = elements[1];

    elements[1] = elements[count];
    elements[count] = 0;
    count--;
    percolateDown();

    return valueToReturn;
}

void priorityQueueBinary::display()
{
    for (int i = 0; i <= count; i++)
    {
        std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}