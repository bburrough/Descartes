#include "dcvector.h"

DCVector::DCVector(Point p_arg)
	: p(p_arg)
{}

DCVector::DCVector(Point origin_arg, Point destination_arg)
{
	p = destination_arg - origin_arg;
}

DCVector::DCVector(LineSegment line_arg)
{
	p = line_arg.GetB() - line_arg.GetA();
}

mm DCVector::Magnitude() const
{
	return sqrt(p.GetX()*p.GetX() + p.GetY()*p.GetY() + p.GetZ()*p.GetZ());
}

mm DCVector::Dot(DCVector v) const
{
	return (p.GetX() * v.p.GetX()) + (p.GetY() * v.p.GetY()) + (p.GetZ() * v.p.GetZ());
}

degrees DCVector::AngleBetween(DCVector v) const
{
	return acos( this->Dot(v) / (this->Magnitude() * v.Magnitude()) ) * (180.0f / PI);
}

DCVector DCVector::operator*(const float& s) const
{
	DCVector temp(*this);
	temp.p.SetX(temp.p.GetX() * s);
    temp.p.SetY(temp.p.GetY() * s);
    temp.p.SetZ(temp.p.GetZ() * s);
    return temp;
}

DCVector DCVector::operator*=(const float& s)
{
	this->p.SetX(this->p.GetX() * s);
    this->p.SetY(this->p.GetY() * s);
    this->p.SetZ(this->p.GetZ() * s);
    return *this;
}

DCVector DCVector::operator/(const float& s) const
{
	DCVector temp(*this);
	temp.p.SetX(temp.p.GetX() / s);
    temp.p.SetY(temp.p.GetY() / s);
    temp.p.SetZ(temp.p.GetZ() / s);
    return temp;
}

DCVector DCVector::operator/=(const float& s)
{
    this->p.SetX(this->p.GetX() / s);
    this->p.SetY(this->p.GetY() / s);
    this->p.SetZ(this->p.GetZ() / s);
    return *this;
}

LRO DCVector::LeftRightOrOn(Point theta) const
{
    // (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
    // (Bx - 0) * (Cy - 0) - (By - 0) * (Cx - 0)
    // Bx * Cy - By * Cx
    float val = p.GetX() * theta.GetY() - p.GetY() * theta.GetX();
    if (FloatsEqual(val, 0.0f))
        return ON;
    else if (val < 0.0f)
        return RIGHT;
    else
        return LEFT;
}
