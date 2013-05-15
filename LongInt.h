#ifndef _LONG_INT_H
#define _LONG_INT_H

#include "classVector.h"
#include <limits.h>
#include <iostream>
#include <string.h>

using namespace std;

namespace my
{
    class LongInt;

    LongInt abs(LongInt const &_x);

    bool operator ==(LongInt const &a, LongInt const &b);
    bool operator ==(LongInt const &a, unsigned char const b);
    bool operator !=(LongInt const &a, LongInt const &b);
    bool operator !=(LongInt const &a, unsigned char const b);
    bool operator <(LongInt const &a, LongInt const &b);
    bool operator <(LongInt const &a, unsigned char const b);
    bool operator >(LongInt const &a, LongInt const &b);
    bool operator >(LongInt const &a, unsigned char const b);
    bool operator <=(LongInt const &a, LongInt const &b);
    bool operator <=(LongInt const &a, unsigned char const b);
    bool operator >=(LongInt const &a, LongInt const &b);
    bool operator >=(LongInt const &a, unsigned char const b);

    LongInt operator +(LongInt const &a, LongInt const &b);
    LongInt operator +(LongInt const &a, unsigned char const b);
    LongInt operator -(LongInt const &a, LongInt const &b);
    LongInt operator -(LongInt const &a, unsigned char const b);
    LongInt operator *(LongInt const &a, LongInt const &b);
    LongInt operator *(LongInt const &a, unsigned char const b);
    LongInt operator /(LongInt const &a, LongInt const &b);
    LongInt operator /(LongInt const &a, unsigned char const b);
    LongInt operator %(LongInt const &a, LongInt const &b);
    unsigned char operator %(LongInt const &a, unsigned char const b);

    istream & operator >>(istream &cin, LongInt &_number);
    ostream & operator <<(ostream &cin, LongInt &_number);
}

class my::LongInt
{
private:

    my::vector<unsigned char> number;
    bool sign;

    void DelZero();
    LongInt NumBaseMultiply(unsigned int const n); // домножение на основание системы счисления в степени n

public:

    LongInt();
    LongInt(int);
    LongInt(LongInt const &);

    ~LongInt();

    friend LongInt abs(LongInt const &_x);

    void operator =(LongInt const &a);

    friend bool operator ==(LongInt const &a, LongInt const &b);
    friend bool operator ==(LongInt const &a, unsigned char const b);
    friend bool operator !=(LongInt const &a, LongInt const &b);
    friend bool operator !=(LongInt const &a, unsigned char const b);
    friend bool operator <(LongInt const &a, LongInt const &b);
    friend bool operator <(LongInt const &a, unsigned char const b);
    friend bool operator >(LongInt const &a, LongInt const &b);
    friend bool operator >(LongInt const &a, unsigned char const b);
    friend bool operator <=(LongInt const &a, LongInt const &b);
    friend bool operator <=(LongInt const &a, unsigned char const b);
    friend bool operator >=(LongInt const &a, LongInt const &b);
    friend bool operator >=(LongInt const &a, unsigned char const b);

    friend LongInt operator +(LongInt const &a, LongInt const &b);
    friend LongInt operator +(LongInt const &a, unsigned char const b);
    friend LongInt operator -(LongInt const &a, LongInt const &b);
    friend LongInt operator -(LongInt const &a, unsigned char const b);
    friend LongInt operator *(LongInt const &a, LongInt const &b);
    friend LongInt operator *(LongInt const &a, unsigned char const b);
    friend LongInt operator /(LongInt const &a, LongInt const &b);
    friend LongInt operator /(LongInt const &a, unsigned char const b);
    friend LongInt operator %(LongInt const &a, LongInt const &b);
    friend unsigned char operator %(LongInt const &a, unsigned char const b);

    LongInt sqr();

    void operator +=(LongInt const &a);
    void operator +=(unsigned char const a);
    void operator -=(LongInt const &a);
    void operator -=(unsigned char const a);
    void operator *=(LongInt const &a);
    void operator *=(unsigned char const a);
    void operator /=(LongInt const &a);
    void operator /=(unsigned char const a);

    friend istream & operator >>(istream &cin, LongInt &_number);
    friend ostream & operator <<(ostream &cin, LongInt &_number);
};

#endif //_LONG_INT_H
