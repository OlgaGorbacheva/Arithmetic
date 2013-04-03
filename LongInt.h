#ifndef _LONG_INT_H
#define _LONG_INT_H

#include "classVector.h"
#include <limits.h>

namespace my
{
    class LongInt;
}

class my::LongInt
{
private:

    my::vector<char> number;
    bool sign;

    void DelZero();

public:

    LongInt();
    LongInt(int);
    LongInt(LongInt &);

};

#endif //_LONG_INT_H
