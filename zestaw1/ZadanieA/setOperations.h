#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <string>
#include <iostream>
#include "setSimple.h"

setSimple setUnion(setSimple A, setSimple B)
{
    setSimple result = setSimple(A.capacity + B.capacity, "Union");
    for (int i = 0; i < A.count; i++)
    {
        result.add(A.elements[i]);
    }

    for (int i = 0; i < B.count; i++)
    {
        if (!result.contains(B.elements[i]))
        {
            result.add(B.elements[i]);
        }
    }
    return result;
}

setSimple setIntersection(setSimple A, setSimple B)
{
    setSimple result = setSimple(A.capacity + B.capacity, "Intersection");
    for (int i = 0; i < A.count; i++)
    {
        if (B.contains(A.elements[i]))
        {
            result.add(A.elements[i]);
        }
    }
    return result;
};

setSimple setDiff(setSimple A, setSimple B)
{
    setSimple result = setSimple(A.capacity + B.capacity, "Difference");
    for (int i = 0; i < A.count; i++)
    {
        if (!B.contains(A.elements[i]))
        {
            result.add(A.elements[i]);
        }
    }
    return result;
};

bool setIdentity(setSimple A, setSimple B)
{
    for (int i = 0; i < A.count; i++)
    {
        if (!B.contains(A.elements[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < B.count; i++)
    {
        if (!A.contains(B.elements[i]))
        {
            return false;
        }
    }
    return true;
};

#endif // SETOPERATIONS_H