/*
 *  Object.cpp
 *  SpaceWars3D
 *
 *  Created by Michael Milvich on Thu Mar 13 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *  $Id: Object.cpp,v 1.13 2003/05/09 17:51:57 milvich Exp $
 */

#include "Object.h"
#include <math.h>

int nextID = 0;

Object::Object(bool powered,bool gravitational) 
{
    fForwardOrientation = Vector3D(0, 1, 0);
    fUpwardOrientation = Vector3D(0, 0, 1);
    fID = nextID;
    nextID++;
    this->powered = powered;
    this->gravitational = gravitational;
    isDead = false;
    if(powered)
    {
	acceleration_list.resize(acceleration_list_length);
	lowest_pointer = 0;
	highest_acceleration_time = 
	    acceleration_list_length * acceleration_delta;
	delta_mult = (int)(floor(highest_acceleration_time/acceleration_delta
				 +
				 acceleration_delta/100.0))
	    -acceleration_list_length;
	assert(delta_mult == 0);
    } else {
	acceleration_list.resize(0);
    }
}

Object::~Object() {};

void Object::reinitializeInertialTensor()
{
   finertial_determinant = fIxx*fIyy*fIzz 
	   - fIxx*fIyz*fIyz
	   - fIyy*fIzx*fIzx
	   - fIzz*fIxy*fIxy
	   + 2*fIxy*fIyz*fIzx;
   fwx=Vector3D(fIyy*fIzz-fIyz*fIyz, fIzx*fIyz-fIxy*fIzz, fIxy*fIyz-fIzx*fIyy);
   fwy=Vector3D(fIyz*fIzx-fIxy*fIzz, fIxx*fIzz-fIzx*fIzx, fIxy*fIzx-fIxx*fIyz);
   fwz=Vector3D(fIxy*fIyz-fIyy*fIzx, fIxy*fIzx-fIxx*fIyz, fIxx*fIyy-fIxy*fIxy);
}


void Object::setForwardOrientation(const Vector3D &v)
{
    Quaternion	q1, q2;
    Vector3D	forward(0,1,0);
    Vector3D	up(0,0,1);
    
    fForwardOrientation = v.normalize();

    q1 = Quaternion(getForwardOrientation().cross(forward), acos(getForwardOrientation().dot(forward)));
    up = q1 * up;
    up = up.normalize();

    q2 = Quaternion(getUpwardOrientation().cross(up), acos(getUpwardOrientation().dot(up)));
    base_q = q1 * q2;
}

void Object::setUpwardOrientation(const Vector3D &v)
{
    Quaternion	q1, q2;
    Vector3D	forward(0,1,0);
    Vector3D	up(0,0,1);
    
    fUpwardOrientation = v.normalize();

    q1 = Quaternion(getForwardOrientation().cross(forward), acos(getForwardOrientation().dot(forward)));
    up = q1 * up;
    up = up.normalize();

    q2 = Quaternion(getUpwardOrientation().cross(up), acos(getUpwardOrientation().dot(up)));
    base_q = q1 * q2;
}


Vector3D Object::getForwardOrientation() const 
{
    return base_q * Vector3D(0, 1, 0);
}

Vector3D Object::getUpwardOrientation() const 
{
    return base_q * Vector3D(0, 0, 1);
}

void Object::draw()
{
    
}

void Object::prepareToDraw()
{
    
}

void Object::moveHighestTime(float time)
{
    if(time > highest_acceleration_time) {
	int new_slots = 
	    (int)ceil((time - highest_acceleration_time)/acceleration_delta);
	for(int l=0; l <= new_slots; l++)
	{
	    //Add a bunch of new zero slots.
	    setUnrolledAcceleration(acceleration_list_length+l,Vector3D());
	}
	lowest_pointer = 
	    (lowest_pointer + new_slots) % acceleration_list_length;
	highest_acceleration_time = highest_acceleration_time 
	    +acceleration_delta * new_slots;
	delta_mult = delta_mult + new_slots;
    }
}

void Object::addAcceleration(float start, float end, Vector3D acceleration) 
{
    moveHighestTime(end);//Make sure can fit end;
    if(start < delta_mult*acceleration_delta)
    {
	//XXX: should probably at least print something if 
	// this happens.
	start = delta_mult*acceleration_delta;
    }
    float start_mult = ceil(start/acceleration_delta) 
	- start/acceleration_delta;
    float end_mult = end/acceleration_delta 
	- floor(end/acceleration_delta);
    int first = (int)floor(start/acceleration_delta)-delta_mult;
    int last = (int)ceil(end/acceleration_delta)-delta_mult;
    if(first == last)
    {
	addAcceleration(first,(start_mult - end_mult)*acceleration);
    } else {
	addAcceleration(first,start_mult*acceleration);
	for(int i = first+1; i < last; i++) {
	    addAcceleration(i,acceleration);
	}
	addAcceleration(last,end_mult*acceleration);
    }
	
}

void Object::addedToUniverse()
{
    
}

void
Object::rotate(Vector3D axis, float angle)
{
    if(angle == 0.0) {
	return;
    }
    //Quaternion u(axis,angle);
    //    Quaternion u_conj = u.getConjugate();
    //Quaternion p_f(0.0,getForwardOrientation());
    //Quaternion p_u(0.0,getUpwardOrientation());
    //setForwardOrientation(u * getForwardOrientation());
    //setUpwardOrientation(u * getUpwardOrientation());
    
    base_q = Quaternion(axis, angle) * base_q;
}

Vector3D 
Object::getRightOrientation()
{
    return (getForwardOrientation().cross(getUpwardOrientation())).normalize();
}
