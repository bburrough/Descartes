#include "linesegment.h"


LineSegment::LineSegment(const Point& A_arg, const Point& B_arg)
    : A(A_arg), B(B_arg)
{}

mm LineSegment::Length() const
{
	return A.Distance(B);
}


Point LineSegment::GetA() const
{
    return A;
}


Point LineSegment::GetB() const
{
    return B;
}
