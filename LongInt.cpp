#include "LongInt.h"

int Pow(int a, unsigned int b) // a^b
{
    if (b == 0)
        return 1;
    int p = 1;
    for (unsigned int i = 0; i < b; i++)
        p *=a;
    return p;
}

void my::LongInt::DelZero()
{
    int i = number.GetSize() - 1;
    while (number.GetSize() > 1 && number[i--] == 0){
        number.DelLast();
    }
}

/////////////////////////////

my::LongInt::LongInt():sign(true)
{ }

my::LongInt::LongInt(int _num)
{
    if (_num < 0){
        sign = false;
        _num = -_num;
    }else sign = true;
    unsigned int sz = sizeof(int);
    unsigned int byte = Pow(2, CHAR_BIT);
    unsigned int mask = byte - 1;
    for (unsigned int i = 0; i < sz; i++){
        unsigned int help = ((mask << i * CHAR_BIT) & _num) / Pow(byte, i);
        number.PushBack((char)help);
    }
    DelZero();
}

my::LongInt::LongInt(LongInt &_num):number(_num.number), sign(_num.sign)
{ }

/////////////////////


