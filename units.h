#ifndef _UNITS_H_
#define _UNITS_H_

/* 12345678911234567892123456789312345678941234567895123456789612345678971234567898 */
#include <cfloat>
#include <cmath>

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
static bool FloatsWithinTolerance(float a, float b, float tolerance)
{
    return (a / b) > 1.0f - tolerance && (a / b) < 1.0f + tolerance;
}


/*
    Compare floats a and b.  Return true if they are within the machine's epsilon
    (FLT_EPSILON) ofeach other.  Note: this is a problematic comparison.  Relevant
    reading: http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
*/
static bool FloatsEqual(float a, float b)
{
    return fabs(a - b) < EPSILON;
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


/*
    isan() simply returns the inverse of isnan.  It's provided to make
    isnan() comparison logic more clear.
*/
#ifndef isan
#define isan(x) (!isnan(x))
#endif

typedef float mm; // millimeters (length)
typedef float mm3; // millimeters cubed (volume)
typedef float mmS; // millimeters per second
typedef float mmS2; // millimeters per second squared
typedef float mm3S; // millimeters cubed per second
typedef float mmM; // millimeters per minute
typedef float degrees;
typedef float seconds;
typedef unsigned int LineNumber;

#endif //_UNITS_H_
