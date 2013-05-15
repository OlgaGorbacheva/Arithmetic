#include "LongInt.h"

int Pow(const int a, const unsigned int b)// a^b
{
    if (b == 0)
        return 1;
    int p = 1;
    for (unsigned int i = 0; i < b; i++)
        p *=a;
    return p;
}

bool InNum(const char c)
{
    return c >= '0' && c <= '9';
}

////////////////////////////

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
    unsigned int byte = Pow(2, CHAR_BIT);
    unsigned int sz = sizeof(int);
    unsigned int mask = byte - 1;
    for (unsigned int i = 0; i < sz; i++){
        unsigned int help = ((mask << i * CHAR_BIT) & _num) / Pow(byte, i);
        number.PushBack((unsigned char)help);
    }
    DelZero();
}

my::LongInt::LongInt(LongInt const &_num):number(_num.number), sign(_num.sign)
{ }

/////////////////////

my::LongInt::~LongInt()
{ }

/////////////////////

my::LongInt my::abs(my::LongInt const &_x)
{
    LongInt x(_x);
    x.sign = true;
    return x;
}

/////////////////////

void my::LongInt::operator =(my::LongInt const &a)
{
    sign = a.sign;
    number = a.number;
}

/////////////////////

bool my::operator ==(my::LongInt const &a, my::LongInt const &b)
{
    if (a.sign != b.sign || a.number.GetSize() != b.number.GetSize())
        return false;
    else
        for(int i = a.number.GetSize() - 1; i >=0; i--){
            if (a.number[i] != b.number[i])
                return false;
        }
    return true;
}

bool my::operator ==(my::LongInt const &a, unsigned char const b)
{
    if (a.number.GetSize() != 1)
        return false;
    int n1 = a.number[0];
    if (!a.sign)
        n1 *= -1;
    return n1 == b;
}

bool my::operator !=(my::LongInt const &a, my::LongInt const &b)
{
    return !(a == b);
}

bool my::operator !=(my::LongInt const &a, unsigned char const b)
{
    return !(a == b);
}

bool my::operator <(my::LongInt const &a, my::LongInt const &b)
{
    if (a.sign != b.sign)
        return !a.sign;
    else
        if (a.sign){
            if (a.number.GetSize() != b.number.GetSize())
                return a.number.GetSize() < b.number.GetSize();
            else
                for(int i = a.number.GetSize() - 1; i >=0; i--)
                    if (a.number[i] != b.number[i])
                        return a.number[i] < b.number[i];
        }
        else{
            if (a.number.GetSize() != b.number.GetSize())
                return a.number.GetSize() > b.number.GetSize();
            else
                for(int i = a.number.GetSize() - 1; i >=0; i--)
                    if (a.number[i] != b.number[i])
                        return a.number[i] > b.number[i];
        }
    return false;
}

bool my::operator <(my::LongInt const &a, unsigned char const b)
{
    if (!a.sign)
        return true;
    if (a.number.GetSize() > 1)
        return false;
    return a.number[0] < b;
}

bool my::operator >(my::LongInt const &a, my::LongInt const &b)
{
    return !((a < b) || (a == b));
}

bool my::operator >(my::LongInt const &a, unsigned char const b)
{
    return !((a < b) || (a == b));
}

bool my::operator <=(my::LongInt const &a, my::LongInt const &b)
{
    return (a < b) || (a == b);
}

bool my::operator <=(my::LongInt const &a, unsigned char const b)
{
    return (a < b) || (a == b);
}

bool my::operator >=(my::LongInt const &a, my::LongInt const &b)
{
    return (a > b) || (a == b);
}

bool my::operator >=(my::LongInt const &a, unsigned char const b)
{
    return (a > b) || (a == b);
}

/////////////////////

my::LongInt my::operator +(my::LongInt const &_a, my::LongInt const &_b)
{
    if (_a.sign == _b.sign){
        LongInt result;
        LongInt a(_a), b(_b);
        unsigned int digit = Pow(2, CHAR_BIT);
        result.sign = a.sign;
        unsigned int help;
        unsigned char r = 0;
        while (a.number.GetSize() < b.number.GetSize())
            a.number.PushBack(0);
        while (b.number.GetSize() < a.number.GetSize())
            b.number.PushBack(0);
        unsigned int n = a.number.GetSize();
        for (unsigned int i = 0; i < n; i++){
            help = a.number[i] + b.number[i] + r;
            result.number[i] = help % digit;
            r = help / digit;
        }
        if (r != 0)
            result.number.PushBack(r);
        return result;
    }
    else{
        if (_a.sign){
            LongInt b(_b);
            b.sign = !b.sign;
            return _a - b;
        }
        else{
            LongInt a(_a);
            a.sign = !a.sign;
            return _b - a;
        }
    }
}

my::LongInt my::operator +(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    LongInt result(_a);
    if (_a.sign){
        unsigned int help = result.number[0] + b;
        result.number[0] = help % digit;
        unsigned int r = help /digit;
        for (int i = 1; r != 0; i++){
            help = result.number[i] + 1;
            result.number[i] = help % digit;
            r = help /digit;
        }
    }
    else{
        if (_a.number.GetSize() == 1 && abs(_a.number[0]) <= b){
            result.sign = false;
            result.number[0] = b - result.number[0];
        }
        else{
            if (_a.number.GetSize() == 1 && abs(result.number[0]) >= b){
                result.sign = true;
                result.number[0] -= b;
            }
            else{
                result = abs(result) - b;
                result.sign = false;
            }
            result.DelZero();
        }
    }
    return result;
}

my::LongInt my::operator -(my::LongInt const &_a, my::LongInt const &_b)
{
    if (_a.sign == _b.sign){
        LongInt result;
        LongInt a, b;
        unsigned int digit = Pow(2, CHAR_BIT);
        unsigned int  help;
        if (_a < _b){  //получаем знак разности и после работаем с числами a и b, причем 0 <= b <= a
            result.sign = false;
            if (abs(_a) < abs(_b)){
                a = abs(_b);
                b = abs(_a);
            }
            else{
                b = abs(_b);
                a = abs(_a);
            }
        }
        else{
            result.sign = true;
            if (abs(_a) < abs(_b)){
                a = abs(_b);
                b = abs(_a);
            }
            else{
                b = abs(_b);
                a = abs(_a);
            }
        }
        result.number = a.number;
        for(unsigned int i = 0; i < b.number.GetSize(); i++){
            if (a.number[i] >= b.number[i])
                result.number[i] -= b.number[i];
            else{
                help = a.number[i] + digit - b.number[i];
                result.number[i] = (char) help;
                int j = i + 1;
                for (; a.number[j] == 0; j++){
                    a.number[j] = digit - 1;
                    result.number[j] = digit - 1;
                }
                a.number[j]--;
                result.number[j]--;
            }
        }
        result.DelZero();
        return result;
    }
    else{
        LongInt b(_b);
        b.sign = !b.sign;
        return _a + b;
    }
}

my::LongInt my::operator -(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    LongInt result(_a);
    if (_a.sign){
        if (_a.number.GetSize() == 1 && _a.number[0] <= b){
            result.sign = false;
            result.number[0] = b - result.number[0];
        }else{
            if (result.number[0] >= b)
                result.number[0] -= b;
            else{
                unsigned int help = _a.number[0] + digit - b;
                result.number[0] = (char) help;
                unsigned int j = 1;
                for (; _a.number[j] == 0; j++){
                    result.number[j] = digit - 1;
                }
                result.number[j]--;
            }
            result.DelZero();
        }
    }
    else{
        unsigned int help = result.number[0] + b;
        result.number[0] = help % digit;
        unsigned int r = help /digit;
        for (int i = 1; r != 0; i++){
            help = result.number[i] + 1;
            result.number[i] = help % digit;
            r = help /digit;
        }
    }
    return result;
}

my::LongInt my::operator *(my::LongInt const &_a, my::LongInt const &_b)
{
    return ((_a + _b).sqr() - (_a - _b).sqr()) / 4;
}

my::LongInt my::operator *(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    LongInt retVal;
    unsigned int help;
    unsigned char r = 0;
    for (unsigned int i = 0; i < _a.number.GetSize(); i++){
        help = _a.number[i] * b + r;
        r = help / digit;
        retVal.number[i] = help % digit;
    }
    if (r != 0)
        retVal.number.PushBack(r);
    return retVal;
}

my::LongInt my::operator /(my::LongInt const &_a, my::LongInt const &_b)
{
    if (_a.number.GetSize() < _b.number.GetSize())
        return 0;
    my::LongInt r, retVal;
    my::vector<unsigned char> result;
    int k;
    int m = _b.number.GetSize(); int n = _a.number.GetSize() - m;
    my::LongInt a;
    for (unsigned int j = n + 1; j < _a.number.GetSize(); j++)
        r.number.PushBack(_a.number[j]);
    for (int i = n; i >= 0; i--){
        my::LongInt a(_a.number[i]);
        a += r.NumBaseMultiply(1);
        if (a.number.GetSize() == _b.number.GetSize()){
            k = a.number[a.number.GetSize() - 1] / _b.number[_b.number.GetSize() - 1];
        }else{
            k = a.number[a.number.GetSize() - 1] * 256 + a.number[a.number.GetSize() - 2];
            k /= _b.number[_b.number.GetSize() - 1];
            if (k > 255) k = 255;
        }
        while (_b * k > a)
            k--;
        result.PushBack(k);
        r = a - _b * k;
    }
    for (int i = result.GetSize() - 1; i >= 0; i--)
        retVal.number.PushBack(result[i]);
    retVal.DelZero();
    return retVal;
}

my::LongInt my::operator /(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    LongInt retVal;
    unsigned int r = 0;
    unsigned int help;
    for (int i = _a.number.GetSize() - 1; i >= 0; i--){
        help = _a.number[i] + r * digit;
        retVal.number[i] = help / b;
        r = help % b;
    }
    retVal.DelZero();
    return retVal;
}

my::LongInt my::operator %(my::LongInt const &_a, my::LongInt const &_b)
{
    if (_a.number.GetSize() < _b.number.GetSize())
        return _a;
    my::LongInt r;
    int k;
    int m = _b.number.GetSize(); int n = _a.number.GetSize() - m;
    my::LongInt a;
    for (unsigned int j = n + 1; j < _a.number.GetSize(); j++)
        r.number.PushBack(_a.number[j]);
    for (int i = n; i >= 0; i--){
        my::LongInt a(_a.number[i]);
        a += r.NumBaseMultiply(1);
        if (a.number.GetSize() == _b.number.GetSize()){
            k = a.number[a.number.GetSize() - 1] / _b.number[_b.number.GetSize() - 1];
        }else{
            k = a.number[a.number.GetSize() - 1] * 256 + a.number[a.number.GetSize() - 2];
            k /= _b.number[_b.number.GetSize() - 1];
            if (k > 255) k = 255;
        }
        while (_b * k > a)
            k--;;
        r = a - _b * k;
    }
    return r;
}

unsigned char my::operator %(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    unsigned char r = 0;
    unsigned int help;
    for (int i = _a.number.GetSize() - 1; i >= 0; i--){
        help = _a.number[i] + r * digit;
        r = help % b;
    }
    return r;
}

void my::LongInt::operator +=(my::LongInt const &a)
{
    (*this) = (*this) + a;
}

void my::LongInt::operator +=(unsigned char const a)
{
    (*this) = (*this) + a;
}

void my::LongInt::operator -=(my::LongInt const &a)
{
    (*this) = (*this) - a;
}

void my::LongInt::operator -=(unsigned char const a)
{
    (*this) = (*this) - a;
}

void my::LongInt::operator *=(my::LongInt const &a)
{
    (*this) = (*this) * a;
}

void my::LongInt::operator *=(unsigned char const a)
{
    (*this) = (*this) * a;
}

void my::LongInt::operator /=(my::LongInt const &a)
{
    (*this) = (*this) / a;
}

void my::LongInt::operator /=(unsigned char const a)
{
    (*this) = (*this) / a;
}

//////////////////////

my::LongInt my::LongInt::NumBaseMultiply(unsigned int const n)
{
    LongInt help;
    for (unsigned int i = 0; i < n; i++)
        help.number[i] = 0;
    for (unsigned int i = 0; i < number.GetSize(); i++)
        help.number[i + n] = number[i];
    help.sign = sign;
    return help;
}

my::LongInt my::LongInt::sqr()
{
    if (number.GetSize() == 1){
        unsigned int help = number[0] * number[0];
        LongInt retVal(help);
        return retVal;
    }
    unsigned int n = number.GetSize() / 2;
    LongInt A(0);
    LongInt B(0);
    for (unsigned int i = 0; i < n; i++)
        A.number[i] = number[i];
    A.sign = sign;
    for (unsigned int i = 0; i < number.GetSize() - n; i++)
        B.number[i] = number[i + n];
    B.sign = sign;
    LongInt retVal;
    LongInt help1 = A + B;
    LongInt help = help1.sqr() - A.sqr() - B.sqr();
    help1 = B.sqr();
    retVal = A.sqr() + help.NumBaseMultiply(n) + help1.NumBaseMultiply(2 * n);
    return retVal;

}

/////////////////////

istream & my::operator >>(istream &cin, my::LongInt &_number)
{
    LongInt help(0);
    LongInt decimal(1);
    LongInt current;
    _number = help;
    char *in;
    try{
        in = new char[1000];
    }
    catch(bad_alloc){
        cerr << "Memory allocation error" << endl;
        return cin;
    }
    cin >> in;
    int j = 0;
    if (in[0] == '-' || in[0] == '+'){
        if (in[0] == '-')
            _number.sign = false;
        else _number.sign = true;
        j++;
    }
    else _number.sign = true;
    for (int i = strlen(in) - 1; i >=j; i--){
        if (!InNum(in[i])){
            throw "Unexpectable input";
            break;
        }
        char n = in[i] - (int)'0';
        current = decimal * n;
        decimal = decimal * 10;
        _number += current;
    }
    return cin;
}

ostream & my::operator <<(ostream &cout, my::LongInt &_number)
{
    my::vector<unsigned char> out;
    if (!_number.sign)
        cout << '-';
    unsigned char help;
    LongInt r = abs(_number);
    if (r.number.GetSize() == 1 && r.number[0] == 0)
        cout << 0;
    while (r > 0){
        help = r % 10;
        out.PushBack(help);
        r = r / 10;
    }
    for (int i = out.GetSize() - 1; i >= 0; i--){
        cout << (int)out[i];
    }
    return cout;
}
