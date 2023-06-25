#include "Vector3D.h"
#include "Point3D.h"
#include <math.h>
#include <stdlib.h>

Vector3D::Vector3D()
{
    fVec[0] = fVec[1] = fVec[2] = fVec[3] = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
    fVec[0] = x;
    fVec[1] = y;
    fVec[2] = z;
    fVec[3] = 0;
}

Vector3D::Vector3D(const Point3D &p1, const Point3D &p2)
{
    fVec[0] = p2[0] - p1[0];
    fVec[1] = p2[1] - p1[1];
    fVec[2] = p2[2] - p1[2];
    fVec[3] = 0;
}

Vector3D::Vector3D(const Point3D &p)
{
    fVec[0] = p[0];
    fVec[1] = p[1];
    fVec[2] = p[2];
    fVec[3] = 0;
}

void Vector3D::set(float x, float y, float z)
{
    fVec[0] = x;
    fVec[1] = y;
    fVec[2] = z;
    fVec[3] = 0;
}

Vector3D Vector3D::operator + (const Vector3D &v) const
{
    Vector3D	temp;

    temp.fVec[0] = fVec[0] + v.fVec[0];
    temp.fVec[1] = fVec[1] + v.fVec[1];
    temp.fVec[2] = fVec[2] + v.fVec[2];

    return temp;
}

Vector3D Vector3D::operator - (const Vector3D &v) const
{
    Vector3D	temp;

    temp.fVec[0] = fVec[0] - v.fVec[0];
    temp.fVec[1] = fVec[1] - v.fVec[1];
    temp.fVec[2] = fVec[2] - v.fVec[2];

    return temp;
}

Vector3D Vector3D::operator * (const float &f) const
{
    Vector3D	temp;

    temp.fVec[0] = fVec[0] * f;
    temp.fVec[1] = fVec[1] * f;
    temp.fVec[2] = fVec[2] * f;

    return temp;
}

Vector3D Vector3D::operator / (const float &f) const
{
    Vector3D	temp;

    temp.fVec[0] = fVec[0] / f;
    temp.fVec[1] = fVec[1] / f;
    temp.fVec[2] = fVec[2] / f;

    return temp;
}

float Vector3D::dot(const Vector3D &v) const
{
    return fVec[0] * v.fVec[0] + fVec[1] * v.fVec[1] + fVec[2] * v.fVec[2];
}

Vector3D Vector3D::cross(const Vector3D &v) const
{
    Vector3D	temp;

    temp.fVec[0] = fVec[1] * v.fVec[2] - fVec[2] * v.fVec[1];
    temp.fVec[1] = fVec[2] * v.fVec[0] - fVec[0] * v.fVec[2];
    temp.fVec[2] = fVec[0] * v.fVec[1] - fVec[1] * v.fVec[0];

    return temp;
}

float Vector3D::mag(void) const
{
    return sqrt(magSquared());
}

float Vector3D::magSquared(void) const
{
    return fVec[0] * fVec[0] + fVec[1] * fVec[1] + fVec[2] * fVec[2];
}

Vector3D Vector3D::operator = (const Vector3D &v)
{
    fVec[0] = v.fVec[0];
    fVec[1] = v.fVec[1];
    fVec[2] = v.fVec[2];
    fVec[3] = 0;

    return v;
}

Vector3D Vector3D::operator - (void) const
{
    Vector3D	temp;

    temp.fVec[0] = -fVec[0];
    temp.fVec[1] = -fVec[1];
    temp.fVec[2] = -fVec[2];

    return temp;
}

bool Vector3D::isClose(const Vector3D &v, const float threshold) const
{
    return (*this - v).magSquared() < threshold;
}

bool Vector3D::operator == (const Vector3D &v) const
{
    return (fVec[0] == v.fVec[0]) && (fVec[1] == v.fVec[1]) && (fVec[1] == v.fVec[1]);
}

bool Vector3D::operator != (const Vector3D &v) const
{
    return (fVec[0] != v.fVec[0]) || (fVec[1] != v.fVec[1]) || (fVec[2] != v.fVec[2]);
}

ostream& operator << (ostream &stream, const Vector3D &v)
{
    stream << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]";

    return stream;
}
