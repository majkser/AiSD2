#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <string>
#include <iostream>
#include "setLinked.h"

setLinked setUnion(setLinked A, setLinked B)
{
    setLinked result = setLinked();

    Node *currentA = A.head;
    Node *currentB = B.head;

    while (currentA != nullptr && currentB != nullptr)
    {
        if (currentA->value == currentB->value)
        {
            result.add(currentA->value);
            currentA = currentA->next;
            currentB = currentB->next;
        }
        else if (currentA->value < currentB->value)
        {
            result.add(currentA->value);
            currentA = currentA->next;
        }
        else if (currentA->value > currentB->value)
        {
            result.add(currentB->value);
            currentB = currentB->next;
        }
    }

    while (currentA != nullptr)
    {
        result.add(currentA->value);
        currentA = currentA->next;
    }
    while (currentB != nullptr)
    {
        result.add(currentB->value);
        currentB = currentB->next;
    }

    return result;
}

setLinked setIntersection(setLinked A, setLinked B)
{
    setLinked result = setLinked();
    Node *currentA = A.head;
    Node *currentB = B.head;

    while (currentA != nullptr && currentB != nullptr)
    {
        if (currentA->value == currentB->value)
        {
            result.add(currentA->value);
            currentA = currentA->next;
            currentB = currentB->next;
        }
        else if (currentA->value < currentB->value)
        {
            currentA = currentA->next;
        }
        else
        {
            currentB = currentB->next;
        }
    }

    return result;
};

setLinked setDiff(setLinked A, setLinked B)
{
    setLinked result = setLinked();
    Node *currentA = A.head;
    Node *currentB = B.head;

    while (currentA != nullptr)
    {
        if (currentB == nullptr)
        {
            result.add(currentA->value);
            currentA = currentA->next;
        }
        else if (currentA->value == currentB->value)
        {
            currentA = currentA->next;
            currentB = currentB->next;
        }
        else if (currentA->value < currentB->value)
        {
            result.add(currentA->value);
            currentA = currentA->next;
        }
        else
        {
            currentB = currentB->next;
        }
    }

    return result;
};

bool setIdentity(setLinked A, setLinked B)
{
    Node *currentA = A.head;
    Node *currentB = B.head;

    while (currentA != nullptr && currentB != nullptr)
    {
        if (currentA->value != currentB->value)
        {
            return false;
        }
        currentA = currentA->next;
        currentB = currentB->next;
    }

    return currentA == nullptr && currentB == nullptr;
};

#endif // SETOPERATIONS_H