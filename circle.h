#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "units.h"
#include "point2.h"
#include <stdint.h>

class Circle
{
public:
	Circle(const Point2& center, const mm& radius, const uint32_t& steps);

//private: // o. m. g.
    Point2 _origin;
    mm _radius;
    uint32_t _steps;
};

#endif //_CIRCLE_H_
