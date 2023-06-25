#include "Point3D.h"
#include "Vector3D.h"
#include <math.h>
#include <stdlib.h>

Point3D::Point3D()
{
    fLoc[0] = fLoc[1] = fLoc[2] = 0;
    fLoc[3] = 1;
}

Point3D::Point3D(float x, float y, float z)
{
    fLoc[0] = x;
    fLoc[1] = y;
    fLoc[2] = z;
    fLoc[3] = 1;
}

Point3D::Point3D(const Vector3D &v)
{
    fLoc[0] = v[0];
    fLoc[1] = v[1];
    fLoc[2] = v[2];
    fLoc[3] = 1;
}

void Point3D::set(float x, float y, float z)
{
    fLoc[0] = x;
    fLoc[1] = y;
    fLoc[2] = z;
    fLoc[3] = 1;
}

Point3D Point3D::operator + (const Vector3D &v) const
{
    Point3D	temp;

    temp.fLoc[0] = fLoc[0] + v[0];
    temp.fLoc[1] = fLoc[1] + v[1];
    temp.fLoc[2] = fLoc[2] + v[2];

    return temp;
}

Point3D Point3D::operator - (const Vector3D &v) const
{
    Point3D	temp;

    temp.fLoc[0] = fLoc[0] - v[0];
    temp.fLoc[1] = fLoc[1] - v[1];
    temp.fLoc[2] = fLoc[2] - v[2];

    return temp;
}

Vector3D Point3D::operator - (const Point3D &p) const
{
    return Vector3D(*this, p);
}

Point3D Point3D::operator * (const float &f) const
{
    Point3D	temp;

    temp.fLoc[0] = fLoc[0] * f;
    temp.fLoc[1] = fLoc[1] * f;
    temp.fLoc[2] = fLoc[2] * f;

    return temp;
}

Point3D Point3D::operator / (const float &f) const
{
    Point3D	temp;

    temp.fLoc[0] = fLoc[0] / f;
    temp.fLoc[1] = fLoc[1] / f;
    temp.fLoc[2] = fLoc[2] / f;

    return temp;
}

Point3D Point3D::operator = (const Point3D &p)
{
    fLoc[0] = p.fLoc[0];
    fLoc[1] = p.fLoc[1];
    fLoc[2] = p.fLoc[2];
    fLoc[3] = 1;

    return p;
}

Point3D Point3D::operator - (void) const
{
    Point3D	temp;

    temp.fLoc[0] = -fLoc[0];
    temp.fLoc[1] = -fLoc[1];
    temp.fLoc[2] = -fLoc[2];

    return temp;
}

bool Point3D::operator == (const Point3D &p) const
{
    return (fLoc[0] == p.fLoc[0]) && (fLoc[1] == p.fLoc[1]) && (fLoc[1] == p.fLoc[1]);
}

bool Point3D::operator != (const Point3D &p) const
{
    return (fLoc[0] != p.fLoc[0]) || (fLoc[1] != p.fLoc[1]) || (fLoc[2] != p.fLoc[2]);
}
