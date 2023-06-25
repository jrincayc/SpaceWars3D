/*!
* @header Point3D
 * This is the header for the Point3D class
 */

#ifndef __POINT3D__
#define __POINT3D__

class Vector3D;

/*!
 * @class Point3D
 *
 * Point3D implements a homogenious point (an extra 4th component that equals one). This
 * is a first class object which means that all of the operations you could do with say an int, you
 * can do with a Point3D, exempt in the cases where it is undefined.
 */
class Point3D
{
protected:
    /*!
     * @var fLoc
     * A float array that contains the 4 componets of a homogenious point.
     */
    float	fLoc[4];

public:
    /*!
     @function Point3D
     @abstract Default constructer. Creates a zero point.
     */
    Point3D();

    /*!
     @function Point3D
     @abstract Creates a point with 3 components.
     @param x The X component
     @param y The Y component
     @param z The Z component
     */
    Point3D(float x, float y, float z);

    /*!
     @function Point3D
     @abstract Creates a point from a vector.
     @param v The vector
     */
    Point3D(const Vector3D &v);

    /*!
     @function set
     @abstract Sets the three setable components.
     @param x The X component
     @param y The Y component
     @param z The Z component
     */
    void set(float x, float y, float z);

    // operators
    Point3D operator + (const Vector3D &v) const;
    Point3D operator - (const Vector3D &v) const;
    Vector3D operator - (const Point3D &p) const;
    Point3D operator * (const float &f) const;
    Point3D operator / (const float &f) const;
    friend Point3D operator * (const float &f, const Point3D &p) {return p * f;}
    Point3D operator - (void) const;
    Point3D operator = (const Point3D &p);
    Point3D operator = (const Vector3D &v);
    Point3D operator += (const Vector3D &v) {return *this = *this + v;}
    Point3D operator -= (const Vector3D &v) {return *this = *this - v;}
    Point3D operator *= (const float &f) {return *this = *this * f;}
    Point3D operator /= (const float &f) {return *this = *this / f;}
    bool operator == (const Point3D &p) const;
    bool operator != (const Point3D &p) const;
    float& operator[] (int x){return fLoc[x];}
    float operator[] (int x) const {return fLoc[x];}

    /*!
     @function getX
     @abstract Returs the X component of the vector.
     @result The X component
     */
    float getX(void) const {return fLoc[0];}

    /*!
     @function getY
     @abstract Returs the Y component of the vector.
     @result The Y component
     */
    float getY(void) const {return fLoc[1];}

    /*!
     @function getZ
     @abstract Returs the Z component of the vector.
     @result The Z component
     */
    float getZ(void) const {return fLoc[2];}
};

#endif
