#ifndef CLASSVECTOR_H
#define CLASSVECTOR_H

#include <string.h>
#include <iostream>
#include <stdlib.h>
#define MIN_MEMORY_SIZE 4

using namespace std;

namespace my
{
    template <class UsingType>
    class vector;
}

template <class UsingType>
class my::vector
{
private:
    unsigned int VectorSize; //number of elements
    unsigned int MemorySize; //number of bytes allocated from heap
    char* Pointer;  //pointer to begin of vector
    void MemoryGrow(); //to reallocate memory
public:
    explicit vector();
    explicit vector(unsigned int); //creat a vector with specified initial MemorySize
    explicit vector(my::vector<UsingType> const & ); // copy a vector
    ~vector();
    void operator=(my::vector<UsingType> const &);
    UsingType const & operator[](unsigned int const) const;
    UsingType & operator[](unsigned int const);
    void PushBack(UsingType);
    void DelLast();
    int GetSize();
};

#include "classVector.cpp"

#endif // CLASSVECTOR_H
