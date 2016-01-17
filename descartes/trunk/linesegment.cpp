#include "linesegment.h"

mm LineSegment::Length()
{
	return A.Distance(B);
}
