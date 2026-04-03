// VectorTest.cpp
//
// Console test program for the Vector template class.
// Tests construction, insertion, addition, deep copy, assignment, and element access operations.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Vector test implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Vector.h"
#include <iostream>

//----------------------------------------------------------------------------
// Runs unit tests for Vector class
int main()
{
    std::cout << "===== VectorTest =====" << std::endl << std::endl;

    std::cout << "-- Test 1 (Constructor) --" << std::endl;
    Vector<int> v1;
    std::cout << "Size: " << v1.Size() << std::endl << std::endl;

    std::cout << "-- Test 2 (Add elements) --" << std::endl;
    v1.Add(10);
    v1.Add(20);
    v1.Add(30);

    std::cout << "Elements: ";
    for (int i = 0; i < v1.Size(); i++)
        std::cout << v1[i] << " ";
    std::cout << std::endl << std::endl;

    std::cout << "-- Test 3 (Insert element) --" << std::endl;
    v1.Insert(1, 15);

    for (int i = 0; i < v1.Size(); i++)
        std::cout << v1[i] << " ";
    std::cout << std::endl << std::endl;

    std::cout << "-- Test 4 (Copy constructor) --" << std::endl;
    Vector<int> v2(v1);

    for (int i = 0; i < v2.Size(); i++)
        std::cout << v2[i] << " ";
    std::cout << std::endl << std::endl;

    std::cout << "-- Test 5 (Assignment operator) --" << std::endl;
    Vector<int> v3;
    v3 = v1;

    for (int i = 0; i < v3.Size(); i++)
        std::cout << v3[i] << " ";
    std::cout << std::endl << std::endl;

    return 0;
}
