/*  -*- C++ -*-
 *  PoweredObject.h
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Thu May 1 2003.
 *  $Id: PoweredObject.h,v 1.6 2003/05/07 16:04:49 jjc Exp $
 */

#ifndef __PoweredObject__
#define __PoweredObject__

#include <algorithm>
#include "Object.h"


class PoweredObject : public Object
{
protected:
    float max_forward_thrust;//and reverse thrust
    float max_up_thrust; // and down thrust
    float max_right_thrust; //and left thrust
    float forward_thrust_percent;
    float up_thrust_percent;
    float right_thrust_percent;
    void addDirectedAcceleration(float start,float end, float percent,
				 Vector3D direction) {
	addAcceleration(start,end,
			(percent/100.0)*direction);
    }

public:
    PoweredObject();
    void setMaxForwardThrust(float forward_thrust)
	{ max_forward_thrust = forward_thrust; }
    float getMaxForwardThrust() const { return max_forward_thrust; }
    void setMaxUpThrust(float up_thrust)
	{ max_up_thrust = up_thrust; }
    float getMaxUpThrust() const { return max_up_thrust; }
    void setMaxRightThrust(float right_thrust)
	{ max_right_thrust = right_thrust; }
    float getMaxRightThrust() const { return max_right_thrust; }
    void setForwardThrustPercent(float forward_thrust)
	{ forward_thrust_percent = std::clamp(-100.0f,forward_thrust,100.0f); }
    float getForwardThrustPercent() const { return forward_thrust_percent; }
    void setUpThrustPercent(float up_thrust)
	{ up_thrust_percent = clamp(-100.0f,up_thrust,100.0f); }
    float getUpThrustPercent() const { return up_thrust_percent; }
    void setRightThrustPercent(float right_thrust)
	{ right_thrust_percent = clamp(-100.0f,right_thrust,100.0f); }
    float getRightThrustPercent() const { return right_thrust_percent; }
    virtual void updateTime(float currentTime, float deltaTime);
    virtual void collide(int id) { setIsDead(true); }
};

#endif //ifndef __PoweredObject__
