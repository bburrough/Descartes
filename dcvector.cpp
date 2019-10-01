#include "dcvector.h"



DCVector::DCVector(const mm& x, const mm& y, const mm& z)
    : Point(x,y,z)
{}


DCVector::DCVector(Point p_arg)
	: Point(p_arg)
{}


DCVector::DCVector(Point origin_arg, Point destination_arg)
    : Point(destination_arg.GetX() - origin_arg.GetX(), destination_arg.GetY() - origin_arg.GetY(), destination_arg.GetZ() - origin_arg.GetZ())
{}


DCVector::DCVector(LineSegment line_arg)
    : Point(line_arg.GetB().GetX() - line_arg.GetA().GetX(), line_arg.GetB().GetY() - line_arg.GetA().GetY(), line_arg.GetB().GetZ() - line_arg.GetA().GetZ())
{}


mm DCVector::Magnitude() const
{
    /*
    FUNDAMENTAL_NUMERIC_TYPE a = GetX().GetValue();
    FUNDAMENTAL_NUMERIC_TYPE b = GetY().GetValue();
    FUNDAMENTAL_NUMERIC_TYPE c = GetZ().GetValue();
    */
    return sqrt(GetX()*GetX() + GetY()*GetY() + GetZ()*GetZ());
}


mm2 DCVector::Dot(const DCVector& v) const
{
	return GetX() * v.GetX() + GetY() * v.GetY() + GetZ() * v.GetZ();
}


degrees DCVector::AngleBetween(DCVector v) const
{
    return degrees(acos(this->Dot(v) / (this->Magnitude() * v.Magnitude())));
}


DCVector DCVector::operator*(const float& s) const
{
	DCVector temp(*this);
	temp.SetX(temp.GetX() * s);
    temp.SetY(temp.GetY() * s);
    temp.SetZ(temp.GetZ() * s);
    return temp;
}


DCVector DCVector::operator*=(const float& s)
{
	this->SetX(this->GetX() * s);
    this->SetY(this->GetY() * s);
    this->SetZ(this->GetZ() * s);
    return *this;
}


DCVector DCVector::operator/(const float& s) const
{
	DCVector temp(*this);
	temp.SetX(temp.GetX() / s);
    temp.SetY(temp.GetY() / s);
    temp.SetZ(temp.GetZ() / s);
    return temp;
}


DCVector DCVector::operator/=(const float& s)
{
    this->SetX(this->GetX() / s);
    this->SetY(this->GetY() / s);
    this->SetZ(this->GetZ() / s);
    return *this;
}


LRO DCVector::LeftRightOrOn(Point theta) const
{
    // (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
    // (Bx - 0) * (Cy - 0) - (By - 0) * (Cx - 0)
    // Bx * Cy - By * Cx
    mm2 val = GetX() * theta.GetY() - GetY() * theta.GetX();
    if (val == 0.0f)
        return ON;
    else if (val < 0.0f)
        return RIGHT;
    else
        return LEFT;
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
