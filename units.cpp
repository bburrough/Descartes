
#include "units.h"


// functions which operate on degrees
degrees::degrees(const radians& x) : _val(x._val  * (180.0f / PI)) {} // conversion constructor


// functions which operate on radians
radians::radians(const degrees& x) : _val(x._val  * (PI / 180.0f)) {} // conversion constructor
mm cos(const radians& x) { return mm(cos(x._val)); }
mm sin(const radians& x) { return mm(sin(x._val)); }
mm tan(const radians& x) { return mm(tan(x._val)); }


// functions which operate on mm
S2 mm::operator/(const mmS2& right) const { return S2(_val / right._val); }
radians acos(const mm& x) { return radians(acos(x._val)); }
seconds mm::operator/(const mmS& right) const { return seconds(_val / right._val); }
mm2 mm::operator*(const mm& right) const { return mm2(_val * right._val); }
mm3 mm::operator*(const mm2& right) const { return mm3(_val * right._val); }
mmS mm::operator/(const seconds& right) const { return mmS(_val / right._val); }


// functions which operate on mm2
mm sqrt(const mm2& x) { return mm(sqrt(x._val)); }
mm3 mm2::operator*(const mm& right) const { return mm3(_val * right._val); }
mm mm2::operator/(const mm& right) const { return mm(_val * right._val); }


// functions which operate on minutes
minutes::minutes(const seconds& x) : _val(x._val / 60.0f) {} // conversion constructor


// functions which operate on seconds
seconds::seconds(const minutes& x) : _val(x._val * 60.0f) {} // conversion constructor
S2 seconds::operator*(const seconds& right) const { return S2(_val * right._val); }


// functions which operate on mmS
mmS::mmS(const mmM& x) : _val(x._val / 60.0f) {} // conversion constructor
seconds mmS::operator/(const mmS2& right) const { return seconds(_val / right._val); }
mm mmS::operator*(const seconds& right) const { return mm(_val * right._val); }
mm2S2 mmS::operator*(const mmS& right) const { return mm2S2(_val * right._val); }
mm3S mmS::operator*(const mm2& right) const { return mm3S(_val * right._val); }


// functions which operate on mmM
mmM::mmM(const mmS& x) : _val(x._val * 60.0f) {} // conversion constructor
mm2M2 mmM::operator*(const mmM& right) const { return mm2M2( _val * right._val ); }


// functions which operate on mmS2
mm mmS2::operator*(const S2& right) const { return mm(_val * right._val); }
mm2S2 mmS2::operator*(const mm& val) const { return mm2S2(_val * val._val); }
mmS sqrt(const mm2S2& x) { return mmS(sqrt(x._val)); }
mmS mmS2::operator*(const seconds& right) const { return mmS(_val * right._val); }


// functions which operate on mm3
mm3S mm3::operator/(const seconds& right) const { return mm3S(_val / right._val); }
mm mm3::operator/(const mm2& right) const { return mm(_val / right._val); }
mm2 mm3::operator/(const mm& right) const { return mm2(_val / right._val); }


// functions which operate on S2
seconds sqrt(const S2& x) { return seconds(sqrt(x._val)); }


// functions which operate on mm3S
mmS mm3S::operator/(const mm2& right) const { return mmS( _val / right._val ); }
mm2 mm3S::operator/(const mmS& right) const { return mm2( _val / right._val ); }
mm3 mm3S::operator*(const seconds& right) const { return mm3(_val / right._val); }


// functions which operate on mm2M2
mmM sqrt(const mm2M2& x) { return mmM(sqrt(x._val)); }




// functions which operate on FUNDAMENTAL_NUMERIC_TYPE
bool isan(const FUNDAMENTAL_NUMERIC_TYPE& x) { return isnan(x) != 0; }
static bool FloatsWithinTolerance(float a, float b, float tolerance)
{
    return (a / b) > 1.0f - tolerance && (a / b) < 1.0f + tolerance;
}


// ***** CANONICAL CLASS IMPLEMENTATION MACRO STARTS HERE *****

#define CANONICAL_IMPLEMENTATION(classname, unitstring) classname::classname() : _val(NAN) {} \
classname::classname(const FUNDAMENTAL_NUMERIC_TYPE& val) : _val(val) {} \
\
/* assignment to own type */ \
/* classname classname::operator=(const classname& right) { _val = right._val; return *this; } */ \
\
/* arithmetic with own type */ \
classname classname::operator+(const classname& right) const { return classname(_val + right._val); } \
classname classname::operator-(const classname& right) const { return classname(_val - right._val); } \
classname classname::operator-() const { return classname(-_val); } \
classname classname::operator+=(const classname& right) { _val += right._val; return *this; } \
classname classname::operator-=(const classname& right) { _val -= right._val; return *this; } \
\
/* unit conversions */ \
FUNDAMENTAL_NUMERIC_TYPE classname::operator/(const classname& right) const { return _val / right._val; } \
\
/* arithmetic with nondimensional values */ \
classname classname::operator*(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return classname(_val * x); } \
classname classname::operator/(const FUNDAMENTAL_NUMERIC_TYPE& x) const  { return classname(_val / x); } \
classname classname::operator*=(const FUNDAMENTAL_NUMERIC_TYPE& x) { _val *= x; return *this; } \
classname classname::operator/=(const FUNDAMENTAL_NUMERIC_TYPE& x) { _val /= x; return *this; } \
classname operator*(const FUNDAMENTAL_NUMERIC_TYPE& x, const classname& right) { return classname(x * right._val); } \
classname operator/(const FUNDAMENTAL_NUMERIC_TYPE& x, const classname& right) { return classname(x / right._val); } \
\
/* comparison with own type */ \
bool classname::operator==(const classname& right) const { return FloatsEqual(_val, right._val); } \
bool classname::operator!=(const classname& right) const { return !FloatsEqual(_val, right._val); } \
bool classname::operator>(const classname& right) const { return _val > right._val; } \
bool classname::operator<(const classname& right) const { return _val < right._val; } \
bool classname::operator>=(const classname& right) const { return _val >= right._val; } \
bool classname::operator<=(const classname& right) const { return _val <= right._val; } \
\
/* comparison with nondimensional values */ \
bool classname::operator==(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return FloatsEqual(_val, x); } \
bool classname::operator!=(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return !FloatsEqual(_val, x); } \
bool classname::operator>(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return _val > x; } \
bool classname::operator<(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return _val < x; } \
bool classname::operator>=(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return _val >= x; } \
bool classname::operator<=(const FUNDAMENTAL_NUMERIC_TYPE& x) const { return _val <= x; } \
\
bool isan(const classname& right) { return !isnan(right._val); } \
bool isnan(const classname& right) { return isnan(right._val) != 0; } \
classname fabs(const classname& right) { return classname(fabs(right._val)); } \
classname safemax(const classname& x, const classname& y) { return classname(safemax(x._val,y._val)); } \
classname safemin(const classname& x, const classname& y) { return classname(safemin(x._val,y._val)); } \
classname clamp(const classname& x, const classname& min, const classname& max) { return classname(clamp(x._val, min._val, max._val)); } \
\
int classname::GetIntValue() const { return (int)_val; } \
float classname::GetFloatValue() const { return (float)_val; } \
\
ostream& operator<<(ostream& os, const classname& right) { os << right._val << " " /*<< unitstring*/; return os; } \
\

// ***** CANONICAL CLASS IMPLEMENTATION MACRO ENDS HERE *****

/*
class mm;
class mm2;
class mm3;
class mmS2;
class mmM;
class radians;
class degrees;
class seconds;
class minutes;
class S2;
class mm2S2;
class mm2M2;
class mmS;
class mm3S;
class degrees_celsius;
*/

CANONICAL_IMPLEMENTATION(mm, "mm");
CANONICAL_IMPLEMENTATION(mm2, "mm²");
CANONICAL_IMPLEMENTATION(mm3, "mm³");
CANONICAL_IMPLEMENTATION(mmS2, "mm/S²");
CANONICAL_IMPLEMENTATION(mmM, "mm/M");
CANONICAL_IMPLEMENTATION(radians, "?");
CANONICAL_IMPLEMENTATION(degrees, "°");
CANONICAL_IMPLEMENTATION(seconds, "S");
CANONICAL_IMPLEMENTATION(minutes, "M");
CANONICAL_IMPLEMENTATION(S2, "S²");
CANONICAL_IMPLEMENTATION(mm2S2, "mm²/S²");
CANONICAL_IMPLEMENTATION(mm2M2, "mm²/M²");
CANONICAL_IMPLEMENTATION(mmS, "mm²");
CANONICAL_IMPLEMENTATION(mm3S, "mm³/S");
CANONICAL_IMPLEMENTATION(degrees_celsius, "?");

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
