

#ifndef __QUATERNIAN__
#define __QUATERNIAN__

#include "Vector3D.h"
#include "Point3D.h"
#include <iostream>

class Quaternion
{
protected:
    Vector3D	v;
    float		w;

public:
    Quaternion();
    Quaternion(const Vector3D &v, const float &rad);
    Quaternion(const float scalar, const Vector3D &v);


    void setVector(const Vector3D &v) {this->v = v;}
    void setWeight(const float &w) {this->w = w;}
    void setAngle(const float &rad);

    Vector3D getVector() const {return v;}
    float getWeight() const {return w;}
    Quaternion getConjugate() const {return Quaternion(w,-v);}

    Point3D operator * (const Point3D &p) const;
    Vector3D operator * (const Vector3D &p) const;
    Quaternion operator * (const Quaternion &p) const;
    
    GLfloat* getGLMatrix();
    
    
    friend ostream& operator << (ostream &stream, const Quaternion &q);
};




#endif
