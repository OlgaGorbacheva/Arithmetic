#ifndef CLASSVECTOR_HPP
#define CLASSVECTOR_HPP
#include "classVector.h"

template <class UsingType>
void my::vector<UsingType>::MemoryGrow()
{
    char* BufPointer;
    BufPointer = new char[MemorySize * 2];
    memcpy(BufPointer, Pointer, MemorySize);
    MemorySize = MemorySize * 2;
    Pointer = BufPointer;
}

template <class UsingType>
my::vector<UsingType>::vector(): VectorSize(0),
                                 MemorySize(MIN_MEMORY_SIZE * sizeof(UsingType))
{
    Pointer = new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(unsigned int _MemorySize): VectorSize(0),
                                                         MemorySize(_MemorySize * sizeof(UsingType))
{
    Pointer = new char[MemorySize];
}

template <class UsingType>
my::vector<UsingType>::vector(my::vector<UsingType> const & _vector): VectorSize(_vector.VectorSize),
                                                                      MemorySize(_vector.MemorySize)
{
    Pointer = new char[MemorySize];
    for (unsigned int i = 0; i < VectorSize; i++){
        new ((UsingType*)Pointer + i) UsingType();
        *((UsingType*)Pointer + i)= _vector[i];
    }
}

template <class UsingType>
my::vector<UsingType>::~vector()
{
    for (unsigned int i = 0; i < VectorSize; i++){
        ((UsingType*)Pointer + i)->~UsingType();
    }
    delete[] Pointer;
}

template <class UsingType>
void my::vector<UsingType>::operator=(my::vector<UsingType> const & _vector)
{
    char* BufPointer;
    BufPointer = new char[_vector.MemorySize];
    delete[] Pointer;
    Pointer = BufPointer;
    MemorySize = _vector.MemorySize;
    VectorSize = _vector.VectorSize;
    for (unsigned int i = 0; i < VectorSize; i++){
        new ((UsingType*)Pointer + i) UsingType();
        *((UsingType*)Pointer + i) = _vector[i];
    }
}

template <class UsingType>
UsingType const & my::vector<UsingType>::operator[](unsigned int const k) const
{
    if (k >= VectorSize)
        throw "Unexpectable index";
    UsingType const & Obj = *((UsingType*)Pointer + k);
    return Obj;
}

template <class UsingType>
UsingType & my::vector<UsingType>::operator[](unsigned int const k)
{
    if (k >= VectorSize){
        try{
            while (k * sizeof(UsingType) >= MemorySize)
                MemoryGrow();
        }
        catch(bad_alloc){
            cerr << "Memory allocation error" << endl;
        }
        for (;VectorSize <= k; VectorSize++){
            new ((UsingType*)Pointer + VectorSize) UsingType();
        }
    }
    UsingType & Obj = *((UsingType*)Pointer + k);
    return Obj;
}

template <class UsingType>
void my::vector<UsingType>::PushBack(UsingType elem)
{
    if (VectorSize * sizeof(UsingType) > MemorySize){
        try{
            MemoryGrow();
        }
        catch(bad_alloc){
            abort();
        }
    }
    (*this)[VectorSize] = elem;
}

template <class UsingType>
void my::vector<UsingType>::DelLast()
{
    VectorSize--;
}

template <class UsingType>
unsigned int my::vector<UsingType>::GetSize() const
{
    return VectorSize;
}

#endif //CLASSVECTOR_HPP
