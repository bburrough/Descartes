#ifndef _LINE_SEGMENT_H_
#define _LINE_SEGMENT_H_

#include "point.h"
#include "units.h"

class LineSegment
{
public:
	Point A;
	Point B;

	mm Length() const;
};

#endif //_LINE_SEGMENT_H_
