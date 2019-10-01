#include "point.h"

#include "dcvector.h"

#include <stdexcept>

using namespace std;


Point::Point()
    : _x(NAN), _y(NAN), _z(NAN)
{}


Point::Point(const mm& x_arg, const mm& y_arg, const mm& z_arg)
    : _x(x_arg), _y(y_arg), _z(z_arg)
{}


Point::~Point()
{
}


bool Point::operator==(const Point& right) const
{
    return _x == right._x && _y == right._y && _z == right._z;
}


Point Point::operator-(const DCVector& right) const
{
    mm x = this->_x - right._x;
    mm y = this->_y - right._y;
    mm z = this->_z - right._z;
    return Point(_x, _y, _z);
}


Point Point::operator-=(const DCVector& right)
{
    *this = *this - right;
    return *this;
}


Point Point::operator+(const DCVector& right) const
{
    mm x = this->_x + right._x;
    mm y = this->_y + right._y;
    mm z = this->_z + right._z;
    return Point(_x, _y, _z);
}


Point Point::operator+=(const DCVector& right)
{
    *this = *this + right;
    return *this;
}


mm Point::GetX() const
{
    return _x;
}


mm Point::GetY() const
{
    return _y;
}


mm Point::GetZ() const
{
    return _z;
}


void Point::SetX(mm x)
{
    _x = x;
}


void Point::SetY(mm y)
{
    _y = y;
}


void Point::SetZ(mm z)
{
    _z = z;
}


mm Point::Distance(Point j) const
{
    if (!IsRational())
        return mm(NAN);

    Point temp = *this - j;

    return sqrt(temp._x*temp._x + temp._y*temp._y + temp._z*temp._z);
}


bool Point::IsRational() const
{
    return isan(_x) && isan(_y) && isan(_z);
}


mm Point::operator[](unsigned int index) const
{
    switch (index)
    {
    case 0:
        return _x;
    case 1:
        return _y;
    case 2:
        return _z;
    default:
        throw(runtime_error("You tried to access an axis of this point that doesn't exist."));
    }
}

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2003-2019 Bobby G. Burrough
Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this 
software, either in source code form or as a compiled binary, for any purpose, 
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this 
software dedicate any and all copyright interest in the software to the public 
domain. We make this dedication for the benefit of the public at large and to 
the detriment of our heirs and successors. We intend this dedication to be an 
overt act of relinquishment in perpetuity of all present and future rights to 
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
