#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion()
{
    w = 1;
}

Quaternion::Quaternion(const Vector3D &v, const float &rad)
{
    float	rad2 = rad / 2;
    w = cos(rad2);
    this->v = v.normalize() * sin(rad2);
}

Quaternion::Quaternion(const float scalar, const Vector3D &v)
{
    float sum, scale;
    
    w = scalar;
    this->v = v;
    
    sum = sqrt(w * w + v.magSquared());
    scale = 1/sum;
    w *= scale;
    this->v[0] *= scale;
    this->v[1] *= scale;
    this->v[2] *= scale;
}

void Quaternion::setAngle(const float &rad)
{
    float rad2 = rad/2;
    w = cos(rad2);
    v = v.normalize() * sin(rad2);
}

Point3D Quaternion::operator * (const Point3D &p) const
{
    return p * (w * w - v.dot(v)) + v.cross(p) * 2 * w + v * (v.dot(p)) * 2;
}

Vector3D Quaternion::operator * (const Vector3D &p) const
{
    return p * (w * w - v.dot(v)) + v.cross(p) * 2 * w + v * (v.dot(p)) * 2;
}

Quaternion Quaternion::operator * (const Quaternion &p) const
{
    float	newW;
    Vector3D	vec;
    
    newW = w * p.w - v[0] * p.v[0] - v[1] * p.v[1] - v[2] * p.v[2];
    vec[0] = w * p.v[0] + v[0] * p.w + v[1] * p.v[2] - v[2] * p.v[1];
    vec[1] = w * p.v[1] - v[0] * p.v[2] + v[1] * p.w + v[2] * p.v[0];
    vec[2] = w * p.v[2] + v[0] * p.v[1] - v[1] * p.v[0] + v[2] * p.w;
    return Quaternion(newW, vec);
    //return Quaternion(w * p.w - v.dot(p.v), v.cross(p.v) + w * p.v + p.w * v);
}

GLfloat* Quaternion::getGLMatrix()
{
    static GLfloat	matrix[16];
    
    float	xx = v[0] * v[0];
    float	xy = v[0] * v[1];
    float	xz = v[0] * v[2];
    float	xw = v[0] * w;

    float 	yy = v[1] * v[1];
    float	yz = v[1] * v[2];
    float	yw = v[1] * w;
    
    float	zz = v[2] * v[2];
    float	zw = v[2] * w;
    
    matrix[0] = 1 - 2 * (yy + zz);
    matrix[1] =     2 * (xy - zw);
    matrix[2] =     2 * (xz + yw);
    
    matrix[4] =     2 * (xy + zw);
    matrix[5] = 1 - 2 * (xx + zz);
    matrix[6] =     2 * (yz - xw);
    
    matrix[8] =     2 * (xz - yw);
    matrix[9] =     2 * (yz + xw);
    matrix[10] =1 - 2 * (xx + yy);
    
    matrix[3] = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0;
    matrix[15] = 1;
    
    return matrix;
}

ostream& operator << (ostream &stream, const Quaternion &q)
{
    stream << "[" << q.v[0] << ", " << q.v[1] << ", " << q.v[2] << "," << q.w << "]";

    return stream;
}
