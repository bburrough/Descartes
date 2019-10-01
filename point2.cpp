#include "point2.h"

#include "dcvector2.h"

Point2::Point2(mm x_arg, mm y_arg)
    : _x(x_arg), _y(y_arg)
{}


Point2::~Point2()
{
}


bool Point2::operator==(const Point2& right) const
{
    return FloatsEqual(_x, right._x) && FloatsEqual(_y, right._y);
}


Point2 Point2::operator-(const DCVector2& right) const
{
    Point2 temp;
    temp._x = this->_x - right._x;
    temp._y = this->_y - right._y;
    return temp;
}


Point2 Point2::operator-=(const DCVector2& right)
{
    *this = *this - right;
    return *this;
}


Point2 Point2::operator+(const DCVector2& right) const
{
    Point2 temp;
    temp._x = this->_x + right._x;
    temp._y = this->_y + right._y;
    return temp;
}


Point2 Point2::operator+=(const DCVector2& right)
{
    *this = *this + right;
    return *this;
}


mm Point2::GetX() const
{
    return _x;
}


mm Point2::GetY() const
{
    return _y;
}


void Point2::SetX(mm x)
{
    _x = x;
}


void Point2::SetY(mm y)
{
    _y = y;
}


mm Point2::Distance(Point2 j) const
{
    if (isnan(_x) || isnan(_y) || isnan(j._x) || isnan(j._y))
        return NAN;

    Point2 temp = *this - j;

    return sqrt(temp._x*temp._x + temp._y*temp._y);
}


bool Point2::IsRational() const
{
    return isan(_x) && isan(_y);
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
