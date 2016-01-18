#include "spiralline.h"

SpiralLine::SpiralLine(const Circle& circle, const DCVector2& direction, const uint32_t& iterations)
	: _circle(circle), _direction(direction), _iterations(iterations)
{}

