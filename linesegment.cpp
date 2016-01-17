#include "linesegment.h"

mm LineSegment::Length() const
{
	return A.Distance(B);
}
