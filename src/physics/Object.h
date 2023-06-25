/*  -*- C++ -*-
 *  Object.h
 *  SpaceWars3D
 *
 *  Created by Michael Milvich on Thu Mar 13 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *  $Id: Object.h,v 1.19 2003/05/09 17:51:57 milvich Exp $
 */

#ifndef __Object__
#define __Object__

#include <vector>
#include "Vector3D.h"
#include "Quaternion.h"
#include <assert.h>
#include <cmath>

class Object
{
protected:
    Vector3D	fVelocityVec;
    Vector3D	fForwardOrientation;
    Vector3D    fUpwardOrientation;
    Vector3D		fLocation;
    float		fRadius;
    float       fmass;
    float       fIxx,fIyy,fIzz,fIxy,fIyz,fIzx;//Components of inertial tensor
    float       finertial_determinant;//Determinate of inertial tensor
    Vector3D    fwx,fwy,fwz;//dot with angular monentum to get compontents 
    //                        of anglular velocity 
	
    int         fID; //Unique id of the object.
    void reinitializeInertialTensor();
    bool       powered;
    bool       gravitational;
    bool       isDead;
    static const int acceleration_list_length = 240;
    static const float acceleration_delta = 1.0/60.0;
    vector<Vector3D> acceleration_list;
    int lowest_pointer;
    float highest_acceleration_time;
    //To get lowest value, take delta_mult*acceleration_delta
    int delta_mult; 

    Vector3D getUnrolledAcceleration(int index) const { 
	return acceleration_list[(index + lowest_pointer) 
				 % acceleration_list_length];
    }

    void  setUnrolledAcceleration(int index, Vector3D vector) { 
	acceleration_list[(index + lowest_pointer) 
			  % acceleration_list_length] = vector;
    }

    void moveHighestTime(float time);
    void addAcceleration(int index, Vector3D acceleration) {
	setUnrolledAcceleration(index,getUnrolledAcceleration(index)+
				acceleration);
    }

    Quaternion	base_q;
    void rotate(Vector3D axis, float angle);


public:
    Object(bool powered=false, bool gravitational=false);
    virtual ~Object();

    Vector3D getAcceleration(float time) const {
	if(!powered || time > highest_acceleration_time 
	   || time < delta_mult*acceleration_delta) 
	{
	    return Vector3D();//zero vector
	} else {
	    int index = (int)floor(time/acceleration_delta)-delta_mult;
	    return getUnrolledAcceleration(index);
	}
    }
    void addAcceleration(float start, float end, Vector3D acceleration);
    Vector3D getVelocityVec() const {return fVelocityVec;}
    Vector3D getForwardOrientation() const;
    Vector3D getUpwardOrientation() const;
    Vector3D getRightOrientation();
    Vector3D getLocation() const {return fLocation;}

    void setVelocityVec(const Vector3D &v) {fVelocityVec = v;}
    void setForwardOrientation(const Vector3D &v);
    void setUpwardOrientation(const Vector3D &v);
    void setLocation(const Vector3D &p) {fLocation = p;}
    void setInertialTensor(float fIxx, float fIyy,float fIzz,
			   float fIxy,float fIyz,float fIzx) 
	    { 
		    this->fIxx = fIxx; this->fIyy = fIyy; this->fIzz = fIzz;
		    this->fIxy = fIxy; this->fIyz = fIyz; this->fIzx = fIzx;
		    reinitializeInertialTensor();	    }

    float getRadius() const {return fRadius;}
    void setRadius(const float &r) {fRadius = r;}
    float getMass() const {return fmass;}
    void setMass(const float m) {fmass = m;}
    int getID() const {return fID; }
    void setIsDead(const bool isDead) {this->isDead = isDead;}
    bool getIsDead() const {return isDead;}
    bool isAlive() const {return !isDead; }
    bool isPowered() const { return powered; }
    bool isGravitational() const { return gravitational; }
    virtual void draw();
    virtual void prepareToDraw();
    virtual void addedToUniverse();
    virtual void updateTime(float currentTime, float deltaTime) {}
    virtual void collide(int id) {}
    virtual uint getResourceID() { return 0; }
    virtual uint getTypeID() { return 0; }

    void yaw(float angle) {rotate(getUpwardOrientation(),angle);}
    void roll(float angle) { rotate(getForwardOrientation(),angle);}
    void pitch(float angle) {rotate(getRightOrientation(),angle); }
    
    Quaternion getRotation() {return base_q;}

};

#endif //ifndef __Object__
