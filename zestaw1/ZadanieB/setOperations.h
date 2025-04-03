#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <string>
#include <iostream>
#include "setLinked.h"

setLinked setUnion(setLinked A, setLinked B)
{
    setLinked result = setLinked();

    Node *currentA = A.head;

    while (currentA != nullptr)
    {
        result.add(currentA->value);
        currentA = currentA->next;
    }

    Node *currentB = B.head;

    while (currentB != nullptr)
    {
        if (!result.contains(currentB->value))
        {
            result.add(currentB->value);
        }
        currentB = currentB->next;
    }

    return result;
}

setLinked setIntersection(setLinked A, setLinked B)
{
    setLinked result = setLinked();
    Node *currentA = A.head;
    while (currentA != nullptr)
    {
        if (B.contains(currentA->value))
        {
            result.add(currentA->value);
        }
        currentA = currentA->next;
    }
    return result;
};

setLinked setDiff(setLinked A, setLinked B)
{
    setLinked result = setLinked();
    Node *currentA = A.head;
    while (currentA != nullptr)
    {
        if (!B.contains(currentA->value))
        {
            result.add(currentA->value);
        }
        currentA = currentA->next;
    }
    return result;
};

bool setIdentity(setLinked A, setLinked B)
{
    Node *currentA = A.head;
    while (currentA != nullptr)
    {
        if (!B.contains(currentA->value))
        {
            return false;
        }
        currentA = currentA->next;
    }

    Node *currentB = B.head;
    while (currentB != nullptr)
    {
        if (!A.contains(currentB->value))
        {
            return false;
        }
        currentB = currentB->next;
    }

    return true;
};

#endif // SETOPERATIONS_H