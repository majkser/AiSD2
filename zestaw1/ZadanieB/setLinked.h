#ifndef setLimple_h
#define setLimple_h
#include <string>
#include <iostream>

struct Node
{
    int value;
    Node *next;

    Node(int value)
    {
        this->value = value;
        this->next = nullptr;
    }
};

class setLinked
{
private:
public:
    setLinked();
    ~setLinked();

    Node *head;
    int count;

    void add(int value);
    void remove(int value);
    bool contains(int value);
    void display();
};

setLinked::setLinked()
{
    head = nullptr;
    count = 0;
}

setLinked::~setLinked()
{
}

void setLinked::add(int value)
{
    if (head == nullptr)
    {
        head = new Node(value);
    }
    else
    {
        Node *current = head;

        if (current->value > value)
        {
            Node *prev = head;
            head = new Node(value);
            head->next = prev;
            return;
        }

        while (current->next != nullptr)
        {
            if (current->next->value > value)
            {
                Node *prev = current->next;
                current->next = new Node(value);
                current->next->next = prev;
                return;
            }
            current = current->next;
        }

        current->next = new Node(value);
    }
}

void setLinked::remove(int value)
{
    if (head == nullptr)
    {
        return;
    }

    if (head->value == value)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *current = head;

    while (current->next != nullptr)
    {
        if (current->next->value == value)
        {
            Node *prev = current;
            prev->next = current->next->next;
            return;
        }

        current = current->next;
    }
}

bool setLinked::contains(int value)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

void setLinked::display()
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    };
    std::cout << std::endl;
}

#endif // setLinked_h