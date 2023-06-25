#include "Affine.h"
#include "math.h"

const float kDegToRadian = .01745329252;

Affine3D::Affine3D(void)
{
    zeroOut();
    fFirstOperation = true;
}

void Affine3D::translate(float x, float y, float z)
{
    Affine3D	temp;

    temp.makeIdentity();
    temp(0,3) = x;
    temp(1,3) = y;
    temp(2,3) = z;

    updateMatrix(temp);
}

void Affine3D::rotate(float x, float y, float z)
{
    Affine3D	rotX, rotY, rotZ;

    float		xR = x * kDegToRadian;
    float		yR = y * kDegToRadian;
    float		zR = z * kDegToRadian;

    float		cosX = cos(xR);
    float		sinX = sin(xR);
    float		cosY = cos(yR);
    float		sinY = sin(yR);
    float		cosZ = cos(zR);
    float		sinZ = sin(zR);

    rotX(0,0) = 1;
    rotX(1,1) = cosX;
    rotX(1,2) = -sinX;
    rotX(2,1) = sinX;
    rotX(2,2) = cosX;

    rotY(0,0) = cosY;
    rotY(0,2) = sinY;
    rotY(1,1) = 1;
    rotY(2,0) = -sinY;
    rotY(2,2) = cosY;

    rotZ(0,0) = cosZ;
    rotZ(0,1) = -sinZ;
    rotZ(1,0) = sinZ;
    rotZ(1,1) = cosZ;
    rotZ(2,2) = 1;

    updateMatrix(rotX);
    updateMatrix(rotY);
    updateMatrix(rotZ);
}

void Affine3D::scale(float x, float y, float z)
{
    Affine3D	scale;

    scale(0,0) = x;
    scale(1,1) = y;
    scale(2,2) = z;

    updateMatrix(scale);
}

Point3D Affine3D::operator * (const Point3D &p)
{
    Point3D	temp;
    float	total;

    for(int row = 0; row < 4; row++)
    {
        total = 0;
        for(int col = 0; col < 4; col++)
        {
            total += fComboMatrix[row][col] * p[col];
        }
        temp[row] = total;
    }
    return temp;
}

Vector3D Affine3D::operator * (const Vector3D &p)
{
    Vector3D	temp;
    float		total;

    for(int row = 0; row < 4; row++)
    {
        total = 0;
        for(int col = 0; col < 4; col++)
        {
            total += fComboMatrix[row][col] * p[col];
        }
        temp[row] = total;
    }
    return temp;
}

Affine3D Affine3D::operator * (const Affine3D &a)
{
    Affine3D	temp;
    float		total;

    for(int row = 0; row < 4; row++)
    {
        for(int k = 0; k < 4; k++)
        {
            total = 0;
            for(int col = 0; col < 4; col++)
            {
                total += fComboMatrix[row][col] * a(col, k);
            }
            temp(row, k) = total;
        }
    }
    return temp;
}

Affine3D Affine3D::operator = (const Affine3D &a)
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            fComboMatrix[row][col] = a(row,col);
        }
    }
    return a;
}

void Affine3D::zeroOut(void)
{
    for(int row = 0; row < 4; row++)
    {
        for(int col = 0; col < 4; col++)
        {
            fComboMatrix[row][col] = 0;
        }
    }
    fComboMatrix[3][3] = 1;
    fFirstOperation = true;
}

void Affine3D::updateMatrix(Affine3D &a)
{
    if(fFirstOperation)
    {
        *this = a;
        fFirstOperation = false;
    }
    else
    {
        *this *= a;
    }
}

void Affine3D::makeIdentity(void)
{
    zeroOut();
    for(int i = 0; i < 4; i++)
    {
        fComboMatrix[i][i] = 1;
    }
}

// copies our 4x4 matrix to a 1 x 16 matrix usally for opengl
void Affine3D::getFlatMatrix(float m[])
{
    for(int col = 0; col < 4; col++)
    {
        for(int row = 0; row < 4; row++)
        {
            m[(row * 4) + col] = fComboMatrix[col][row];
        }
    }
}
