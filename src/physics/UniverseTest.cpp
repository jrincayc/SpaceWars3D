/*
 *  UniverseTest.cpp
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Fri Apr 11 2003.
 *  $Id: UniverseTest.cpp,v 1.1 2003/04/11 22:08:49 jjc Exp $
 */

#include <iostream>
#include "Universe.h"

int main()
{
    Universe universe;
    Object sun, moon;
    sun.setLocation(Vector3D(0.0,0.0,0.0));
    moon.setLocation(Vector3D(10000.0,0.0,0.0));
    sun.setVelocityVec(Vector3D(0.0,-0.05,0.0));
    moon.setVelocityVec(Vector3D(0.0,50.0,0.0));
    sun.setMass(100000000.0);
    moon.setMass(100000.0);
    universe.addGravitationalObject(&sun);
    universe.addGravitationalObject(&moon);
    for(int i = 0; i < 1000; i++)
    {
	universe.gotoNextTime(1.0);
	cout << i; 
	cout << "\tsun: " <<sun.getLocation().getX() << " " 
	     << sun.getLocation().getY() << " " << sun.getLocation().getZ();
	cout << "\tsunv: " <<sun.getVelocityVec().getX() << " " 
	     << sun.getVelocityVec().getY() << " " << sun.getVelocityVec().getZ();

	cout << "\tmoon: ";
	cout << moon.getLocation().getX() << " " << moon.getLocation().getY()
	     << " " << moon.getLocation().getZ();
	cout << "\tvmoon: ";
	cout << moon.getVelocityVec().getX() << " " << moon.getVelocityVec().getY()
	     << " " << moon.getVelocityVec().getZ() << endl;
    }
}
