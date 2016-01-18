#ifndef _SPIRAL_LINE_H_
#define _SPIRAL_LINE_H_

#include "circle.h"
#include "dcvector2.h"

class SpiralLine
{
public:
	SpiralLine(const Circle& circle, const DCVector2& direction, const uint32_t& iterations);

//private:	// o. m. g.
    Circle _circle;
    DCVector2 _direction;
    uint32_t _iterations;
};

#endif //_SPIRAL_LINE_H_
