#include "Point3D.h"
#include "Vector3D.h"

#ifndef __Affine3D__
#define __Affine3D__


class Affine3D
{
protected:
    float	fComboMatrix[4][4];
    bool	fFirstOperation;

public:
    Affine3D();

    void translate(float x, float y, float z);
    void translate(const Point3D &p1) {translate(p1[0], p1[1], p1[2]);}
    void translate(const Vector3D &v) {translate(v[0], v[1], v[2]);}
    void rotate(float x, float y, float z);
    void scale(float x, float y, float z);
    void scale(float s) { scale(s, s, s);}

    void makeIdentity(void);

    Point3D operator * (const Point3D &p);
    Vector3D operator * (const Vector3D &p);

    Affine3D operator * (const Affine3D &a);

    Affine3D operator = (const Affine3D &a);

    Affine3D operator *= (const Affine3D &a) {return *this = *this * a;}

    void zeroOut(void);	// leaves a one in [3][3]

    float& operator () (int row, int col) { return fComboMatrix[row][col];}
    float operator () (int row, int col) const { return fComboMatrix[row][col];}

    void getFlatMatrix(float m[]);

protected:
    void updateMatrix(Affine3D &a);
};

#endif
