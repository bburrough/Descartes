#ifndef _POINT_H_
#define _POINT_H_

#include "units.h"

class DCVector;

/*
    Represents a three dimensional point in space.  Units
    of measure are millimeters.
*/
class Point
{
public:
    Point();
    Point(const mm& x_arg, const mm& y_arg, const mm& z_arg);
    virtual ~Point();

    bool operator==(const Point& right) const;
    Point operator-(const DCVector& right) const;
    Point operator-=(const DCVector& right);
    Point operator+(const DCVector& right) const;
    Point operator+=(const DCVector& right);
    mm operator[](unsigned int index) const;

    mm GetX() const;
    mm GetY() const;
    mm GetZ() const;

    void SetX(mm x);
    void SetY(mm y);
    void SetZ(mm z);

    /*
        Returns the distance between this point and j
        in millimeters.
    */
    mm Distance(Point j) const;

    /*
        IsRational is used to check whether this Point
        is complete.  It will return true if x, y, and z
        are actual values.  It will return false if they
        are not numbers.
    */
    bool IsRational() const;


private:
    mm _x;
    mm _y;
    mm _z;
};


/*
class Point4 : public Point
{
    bool operator==(const Point& right) const;
    Point operator-(const DCVector& right) const;
    Point operator-=(const DCVector& right);
    Point operator+(const DCVector& right) const;
    Point operator+=(const DCVector& right);

};
*/

#endif //_POINT_H_

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
