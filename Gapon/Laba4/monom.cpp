#include <iostream>
#include "monom.h"
using namespace std;


bool operator < (const link& x, const link& y)
{
    if (x.pow < y.pow) return true;
    return false;
}

bool operator >= (const link& x, const link& y) 
{
    if (x.pow >= y.pow) return true;
    return false;
}

bool operator == (const link& x, const link& y)
{
    if (x.pow == y.pow) return true;
    return false;
}

link operator*(const link& x, const link& y) 
{
    link res;
    res.pow = x.pow + y.pow;
    res.a = x.a * y.a;
    return res;
}

ostream& operator<<(ostream& out, const link& t) 
{ 
    int pow = t.pow;
    int powx = pow % 20;
    pow /= 20;
    int powy = pow % 20;
    pow /= 20;
    int powz = pow % 20;
    pow /= 20;
    out << "(" << t.a << " * ";
    out << "x^" << powx << " * y^" << powy << " * z^" << powz << ")";
    return out;
}
istream& operator>>(istream& in, link& t) 
{
    int powx, powy, powz;
    in >> t.a >> powx >> powy >> powz;
    t.pow = powx + powy * 20 + powz * 400;
    return in;
}