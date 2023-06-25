/*
 *  UniverseTest.cpp
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Fri Apr 11 2003.
 *  $Id: UniverseTest2.cpp,v 1.1 2003/04/29 03:03:30 jjc Exp $
 */

#include <iostream>
#include "Universe.h"

int main()
{
    Universe universe;
    Object rocket(true,false);
    rocket.setLocation(Vector3D(0.0,0.0,0.0));
    rocket.addAcceleration(0.0,0.6,Vector3D(1.0,0.0,0.0));
    rocket.addAcceleration(1.0,1.5,Vector3D(1.0,0.0,0.0));
    rocket.addAcceleration(1.2,1.7,Vector3D(0.0,1.0,0.0));
    rocket.addAcceleration(2.15,2.35,Vector3D(-5.5,0.0,0.0));
    universe.addPoweredObject(&rocket);
    int id = rocket.getID();
    for(int i = 0; i < 1000; i++)
    {
	universe.gotoNextTime(0.01);
	float currentTime = universe.getLastValidTime();
	cout << i << "\t" << currentTime; 
	cout << "\trocket: " << universe.getObjectLocation(currentTime,id);
	cout << "\trocketv: " <<universe.getObjectVelocity(currentTime,id)
	     << endl;
    }
}
