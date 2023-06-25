/*
 *  PoweredObject.cpp
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Thu May 1 2003.
 *  $Id: PoweredObject.cpp,v 1.3 2003/05/07 16:04:49 jjc Exp $
 */

#include "PoweredObject.h"


PoweredObject::PoweredObject() :
    Object::Object(true,false)
{
    max_forward_thrust = 1.0;
    max_up_thrust = 1.0; 
    max_right_thrust = 1.0;
    forward_thrust_percent = 0.0;
    up_thrust_percent = 0.0;
    right_thrust_percent = 0.0;
}


void 
PoweredObject::updateTime(float currentTime, float deltaTime) 
{
    float end_time = currentTime+deltaTime;
    if(forward_thrust_percent != 0.0)
    {
	addDirectedAcceleration(currentTime,end_time,forward_thrust_percent,
				max_forward_thrust*getForwardOrientation());
    }
    if(up_thrust_percent != 0.0)
    {
	addDirectedAcceleration(currentTime,end_time,up_thrust_percent,
				max_up_thrust*getUpwardOrientation());
    }
    if(right_thrust_percent != 0.0)
    {
	addDirectedAcceleration(currentTime,end_time,right_thrust_percent,
				max_right_thrust*getRightOrientation());
    }
}
