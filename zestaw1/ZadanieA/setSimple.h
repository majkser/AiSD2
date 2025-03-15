#ifndef setSimple_h
#define setSimple_h

#include <string>
#include <iostream>

class setSimple
{
private:
public:
    setSimple(int size, std::string name);
    ~setSimple();

    int *elements;
    int capacity;
    int count;

    void add(int value);
    void remove(int value);
    bool contains(int value);
    void display();
};

setSimple::setSimple(int size, std::string name)
{
    std::cout << "setSimple constructor name: " << name << std::endl;
    capacity = size;
    count = 0;
    elements = new int[capacity];
}

setSimple::~setSimple()
{
}

void setSimple::add(int value)
{
    elements[count++] = value;
}

void setSimple::remove(int value)
{
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == value)
        {
            elements[i] = elements[count - 1];
            count--;
            break;
        }
    }
}

bool setSimple::contains(int value)
{
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == value)
        {
            return true;
        }
    }
    return false;
}

void setSimple::display()
{
    for (int i = 0; i < count; i++)
    {
        std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}

#endif // setSimple_h