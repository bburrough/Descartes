#ifndef _UNITS_H_
#define _UNITS_H_

#include <cfloat>
#include <cmath>

using namespace std;

#define PI 3.1415926535897932384626433832f
#define EPSILON FLT_EPSILON

static bool FloatsWithinTolerance(float a, float b, float tolerance)
{
    return (a / b) > 1.0f - tolerance && (a / b) < 1.0f + tolerance;
}

static bool FloatsEqual(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

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
