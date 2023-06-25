/*!
 * @header Vector3D
 * This is the header for the Vector3D class
 */

#ifndef __VECTOR3D__
#define __VECTOR3D__

#include <ostream>
#include "GLHeaders.h"

using namespace std;

class Point3D;

/*!
 * @class Vector3D
 *
 * Vector3D implements a homogenious vector (an extra 4th component that equals zero). This
 * is a first class object which means that all of the operations you could do with say an int, you
 * can do with a Vector3D, exempt in the cases where it is undefined.
 */
class Vector3D
{
protected:
    /*!
     * @var fVec
     * A float array that contains the 4 componets of a homogenious vector.
     */
    float	fVec[4];	

public:
    /*!
     @function Vector3D
     @abstract Default constructer. Creates a zero vector.
     */
    Vector3D();

    /*!
     @function Vector3D
     @abstract Creates a vector with 3 components.
     @param x The X component
     @param y The Y component
     @param z The Z component
     */
    Vector3D(float x, float y, float z);

    /*!
     @function Vector3D
     @abstract Creates a vector from p1 to p2.
     @param p1 The originating point
     @param p2 The final point
     */
    Vector3D(const Point3D &p1, const Point3D &p2);

    /*!
     @function Vector3D
     @abstract Creates a vector from (0,0,0) to p
     @param p The point to create a vector to
     */
    Vector3D(const Point3D &p);

    /*!
     @function set
     @abstract Sets the three setable components.
     @param x The X component
     @param y The Y component
     @param z The Z component
     */
    void set(float x, float y, float z);

    // operators
    Vector3D operator + (const Vector3D &v) const;
    Vector3D operator - (const Vector3D &v) const;
    Vector3D operator * (const float &f) const;
    Vector3D operator / (const float &f) const;
    friend Vector3D operator * (const float &f, const Vector3D &v) {return v * f;}
    Vector3D operator - (void) const;
    Vector3D operator = (const Vector3D &v);
    Vector3D operator += (const Vector3D &v) {return *this = *this + v;}
    Vector3D operator -= (const Vector3D &v) {return *this = *this - v;}
    Vector3D operator *= (const float &f) {return *this = *this * f;}
    Vector3D operator /= (const float &f) {return *this = *this / f;}
    bool operator == (const Vector3D &v) const;
    bool operator != (const Vector3D &v) const;
    float& operator[] (int x){return fVec[x];}
    float operator[] (int x) const {return fVec[x];}
    friend ostream& operator << (ostream &stream, const Vector3D &v);

    /*!
     @function dot
     @abstract Dots two vectors and returns the result.
     @param v The vector to dot with
     @result A scaler dot product.
     */
    float dot(const Vector3D &v) const;

    /*!
     @function cross
     @abstract Crosses two vectors and returns the result.
     @param v The vector to cross with
     @result A Vector3D that is perpendicular to both vectors.
     */
    Vector3D cross(const Vector3D &v) const;

    /*!
     @function mag
     @abstract Figures out the magintude of the vector and returns it.
     @result The length or magintude of the vector
     */
    float mag(void) const;

    /*!
     @function magSquared
     @abstract Figures out the magnitude squared of the vector and returns it.
     @discussion When compairing a vector to a vector, you may not need the real maginuted which
     requires a square root. This is provided to speed up any such comparsions by not doing the
     square root.
     @result The magintude^2 of a vector
     */
    float magSquared(void) const;

    /*!
     @function normalize
     @abstract Normalizes the vector and returns the result.
     @result A Vector3D that has a length of 1
     */
    Vector3D normalize(void) const {float mag = this->mag(); return *this / ((mag == 0.0) ? 1.0 : mag);}

    /*!
     @function makeSize
     @abstract Normalizes the vector and then multiplies it by size to create a new vector with a
     magnitude of size.
     @param size The size of the new vector.
     @result A Vector3D with a length of size, and retains the same direction as the original.
     */
    Vector3D makeSize(float size) const {return this->normalize() * size;}

    /*!
     @function isClose
     @abstract Checks to see if the components of a vector are within a certain threshold of another vector.
     @param v The vector to check against
     @param threshold The threshold
     @result true if within threshold, otherwise false
     */
    bool isClose(const Vector3D &v, const float threshold) const;

    /*!
     @function getX
     @abstract Returns the X component of the vector.
     @result The X component
     */
    float getX(void) const {return fVec[0];}
    
    /*!
     @function getY
     @abstract Returns the Y component of the vector.
     @result The Y component
     */
    float getY(void) const {return fVec[1];}
    
    /*!
     @function getZ
     @abstract Returns the Z component of the vector.
     @result The Z component
     */
    float getZ(void) const {return fVec[2];}

    /*!
     @function glVertex
     @abstract Calls the gl function glVertex3f to draw this point
     */
    void glVertex() {glVertex3f(fVec[0], fVec[1], fVec[2]);}
};

#endif
