#ifndef _LINE_SEGMENT_H_
#define _LINE_SEGMENT_H_

#include "point.h"
#include "units.h"

class LineSegment
{
public:
    LineSegment(const Point& A_arg, const Point& B_arg);
	mm Length() const;

    Point GetA() const;
    Point GetB() const;

private:
    Point A;
    Point B;
};

#endif //_LINE_SEGMENT_H_
