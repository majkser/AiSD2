#ifndef dictionarySimple_h
#define dictionarySimple_h

#include <string>
#include <iostream>

class dictionarySimple
{
private:
public:
    dictionarySimple(int size);
    ~dictionarySimple();

    std::string *elements;
    int capacity;
    int count;

    void add(std::string value);
    void remove(std::string value);
    bool contains(std::string value);
    void display();
};

dictionarySimple::dictionarySimple(int size)
{
    // std::cout << "dictionarySimple constructor name: " << name << std::endl;
    capacity = size;
    count = 0;
    elements = new std::string[capacity];
}

dictionarySimple::~dictionarySimple()
{
}

void dictionarySimple::add(std::string value)
{
    if (count < capacity)
    {
        elements[count++] = value;
    }
    else
    {
        std::cout << "Dictionary is full" << std::endl;
    }
}

void dictionarySimple::remove(std::string value)
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

bool dictionarySimple::contains(std::string value)
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

void dictionarySimple::display()
{
    for (int i = 0; i < count; i++)
    {
        std::cout << elements[i] << " ";
    }
    std::cout << std::endl;
}

#endif // dictionarySimple_h