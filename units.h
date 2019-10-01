#ifndef _UNITS_H_
#define _UNITS_H_

/* 12345678911234567892123456789312345678941234567895123456789612345678971234567898 */
#include <cfloat>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

/*
    PI out to silly precision.  Relevant reading:
    http://blogs.scientificamerican.com/observations/how-much-pi-do-you-need/
*/
#define PI 3.1415926535897932384626433832f
#define EPSILON FLT_EPSILON


/*
    LRO is an enum that represents whether something is to
    the left or right of something else, or whether they
    are practically colinear.
*/
enum LRO
{
    ON,
    LEFT,
    RIGHT
};


/*
    Compare floats a and b.  Return true if they are nearer to each other than the
    tolerance.  Otherwise, return false.
*/
static bool FloatsWithinTolerance(float a, float b, float tolerance);

/*
    Compare floats a and b.  Return true if they are within the machine's epsilon
    (FLT_EPSILON) ofeach other.  Note: this is a problematic comparison.  Relevant
    reading: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
*/
static bool FloatsEqual(float a, float b)
{
    return fabs(a - b) < EPSILON;
}


static float safemax(float a, float b)
{
    if (isnan(a) && isnan(b))
        return NAN;
    else if (isnan(a) && !isnan(b))
        return b;
    else if (!isnan(a) && isnan(b))
        return a;
    else
        return max(a, b);
}


static float safemin(float a, float b)
{
    if (isnan(a) && isnan(b))
        return NAN;
    else if (isnan(a) && !isnan(b))
        return b;
    else if (!isnan(a) && isnan(b))
        return a;
    else
        return min(a, b);
}


static float safemax(const float values[], const size_t& n)
{
    float max = NAN;
    for (size_t i = 0; i < n; i++)
        max = safemax(max, values[i]);
    return max;
}


static float clamp(const float x, const float min, const float max)
{
    if (x > max)
        return max;
    if (x < min)
        return min;
    return x;
}


/*
    Windows (in its abject laziness) doesn't provide isnan().  Therefore, we
    provide it (and relatives) here.
*/
#if WIN32
#ifndef NAN
static const unsigned long __nan[2] = { 0xffffffff, 0x7fffffff };
#define NAN (*(const float *) __nan)
#endif

#ifndef isnan
#define isnan(x) _isnan(x)
#endif

#ifndef isinf
#define isinf(x) (!_finite(x))
#endif

#ifndef fpu_error
#define fpu_error(x) (isinf(x) || isnan(x))
#endif
#endif

#define FUNDAMENTAL_NUMERIC_TYPE float

/*
    isan() simply returns the inverse of isnan.  It's provided to make
    isnan() comparison logic more clear.
*/
/*
#ifndef isan
#define isan(x) (!isnan(x))
#endif
*/
bool isan(const FUNDAMENTAL_NUMERIC_TYPE& x);


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


#define CANONICAL_DECLARATIONS(classname) classname(); \
explicit classname(const FUNDAMENTAL_NUMERIC_TYPE& val); \
\
/* assignment to own type */ \
/* classname operator=(const classname& right); */ \
\
/* arithmetic with own type */ \
classname operator+(const classname& right) const; \
classname operator-(const classname& right) const; \
classname operator-() const; \
classname operator+=(const classname& right); \
classname operator-=(const classname& right); \
\
/* unit conversions */ \
FUNDAMENTAL_NUMERIC_TYPE operator/(const classname& right) const; \
\
/* arithmetic with nondimensional values */ \
classname operator*(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
classname operator/(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
classname operator*=(const FUNDAMENTAL_NUMERIC_TYPE& x); \
classname operator/=(const FUNDAMENTAL_NUMERIC_TYPE& x); \
friend classname operator*(const FUNDAMENTAL_NUMERIC_TYPE& x, const classname& right); \
friend classname operator/(const FUNDAMENTAL_NUMERIC_TYPE& x, const classname& right); \
\
/* comparison with own type */ \
bool operator==(const classname& right) const; \
bool operator!=(const classname& right) const; \
bool operator>(const classname& right) const; \
bool operator<(const classname& right) const; \
bool operator>=(const classname& right) const; \
bool operator<=(const classname& right) const; \
\
/* comparison with nondimensional values */ \
bool operator==(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
bool operator!=(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
bool operator>(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
bool operator<(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
bool operator>=(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
bool operator<=(const FUNDAMENTAL_NUMERIC_TYPE& x) const; \
\
friend bool isan(const classname& right); \
friend bool isnan(const classname& right); \
friend classname fabs(const classname& right); \
friend classname safemax(const classname& x, const classname& y); \
friend classname safemin(const classname& x, const classname& y); \
friend classname clamp(const classname& x, const classname& min, const classname& max); \
\
int GetIntValue() const; \
float GetFloatValue() const; \
\
friend ostream& operator<<(ostream& os, const classname& right); \
\


// degrees of rotation - measure of angles
class degrees
{
public:
    friend class radians;
    degrees(const radians& x);

    CANONICAL_DECLARATIONS(degrees);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// radians - measure of angles
class radians
{
public:
    friend class degrees;
    radians(const degrees& x);

    CANONICAL_DECLARATIONS(radians);

    friend mm cos(const radians& x);
    friend mm sin(const radians& x);
    friend mm tan(const radians& x);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters - measure of length or distance
class mm
{
public:
    friend class mmS2;
    friend class mm2;
    friend class mm3;

    CANONICAL_DECLARATIONS(mm);

    // unit conversions
    mm2 operator*(const mm& right) const;
    seconds operator/(const mmS& right) const;
    S2 operator/(const mmS2& right) const;
    mm3 operator*(const mm2& right) const;
    mmS operator/(const seconds& right) const;

    // loose functions
    friend radians acos(const mm& x);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// seconds squared - component of the value of acceleration (for acceleration use mmS2)
class S2
{
public:
    friend class mmS2;

    CANONICAL_DECLARATIONS(S2);

    // loose functions
    friend seconds sqrt(const S2& val);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


class mmS2
{
public:
    friend class mm;
    friend class mmS;

    CANONICAL_DECLARATIONS(mmS2);
    
    // arithmetic with mmS2
    // const mmS2& operator-() const; // TODO: Do we want this in the canonical definitoins? i.e. Do we want to support negative velocities? Additionally, if we don't support negative velocities, subtraction must be clamped.
   
    // unit conversions
    mm2S2 operator*(const mm& val) const;
    mm operator*(const S2& right) const;
    mmS operator*(const seconds& right) const;

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters cubed per second - unit of volumetric velocity
class mm3S
{
public:
    friend class mm3;

    CANONICAL_DECLARATIONS(mm3S);

    //const mm3S& operator/(const unsigned int& right) const; // TODO: Why is this here?

    // unit conversions
    mmS operator/(const mm2& right) const;
    mm2 operator/(const mmS& right) const;
    mm3 operator*(const seconds& right) const;

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millilmeters per minute - unit of linear velocity
class mmM
{
public:
    friend class mmS;
    mmM(const mmS& x); // convert from mmS

    CANONICAL_DECLARATIONS(mmM);

    // unit conversions
    mm2M2 operator*(const mmM& right) const;

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters per second - unit of linear velocity
class mmS
{
public:
    friend class mm;
    friend class mmM;
    friend class mm3S;

    mmS(const mmM& x); // convert from mmM

    CANONICAL_DECLARATIONS(mmS);
    
    // unit conversions
    seconds operator/(const mmS2& right) const;
    mm operator*(const seconds& right) const;
    mm2S2 operator*(const mmS& right) const;
    mm3S operator*(const mm2& right) const;

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// seconds - unit of time
class seconds
{
public:
    friend class mm;
    friend class mm3;
    friend class mmS;
    friend class mmS2;
    friend class minutes;
    friend class mm3S;

    seconds(const minutes& x);

    CANONICAL_DECLARATIONS(seconds);

    // unit conversions
    S2 operator*(const seconds& right) const;

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// minutes - unit of time
class minutes
{
public:
    friend class seconds;
    minutes(const seconds& x); // convert seconds into minutes

    CANONICAL_DECLARATIONS(minutes);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// temperature in degrees Celsius
class degrees_celsius
{
public:
    CANONICAL_DECLARATIONS(degrees_celsius);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


typedef uint32_t LineNumber;

static const degrees_celsius room_temperature(23.0f);


// millimeters squared - measure of area
class mm2
{
public:
    friend class mm;
    friend class mmS;
    friend class mm3;
    friend class mm3S;

    CANONICAL_DECLARATIONS(mm2);

    // unit conversions
    mm3 operator*(const mm& x) const;
    mm operator/(const mm& x) const;

    // loose functions
    friend mm sqrt(const mm2& x);
    friend mm2 operator*(const FUNDAMENTAL_NUMERIC_TYPE& left, const mm2& right);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters cubed - measure of volume
class mm3
{
public:
    CANONICAL_DECLARATIONS(mm3);

    // unit conversions
    mm3S operator/(const seconds& x) const;
    mm operator/(const mm2& x) const;
    seconds operator/(const mm3S& x) const;
    mm2 operator/(const mm& right) const;

    // loose functions
    //friend const mm2& operator*(const FUNDAMENTAL_NUMERIC_TYPE& left, const mm3& right); // TODO: This declaration has the wrong return type.

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters squared divided by seconds squared - this is primarily used as an intermediate factor which subsequently is converted to mmS via sqrt
class mm2S2
{
public:
    CANONICAL_DECLARATIONS(mm2S2);

    // loose functions
    friend mmS sqrt(const mm2S2& x);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};


// millimeters squared divided by minutes squared - this is primarily used as an intermediate factor which subsequently is converted to mmM via sqrt
class mm2M2
{
public:
    CANONICAL_DECLARATIONS(mm2M2);

    // loose functions
    friend mmM sqrt(const mm2M2& x);

private:
    FUNDAMENTAL_NUMERIC_TYPE _val;
};

#endif //_UNITS_H_

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
