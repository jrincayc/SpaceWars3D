/*  -*- C++ -*-
 *  ShipInput.h
 *  SpaceWars3D
 *
 *  $Id: ShipInput.h,v 1.5 2003/05/09 22:08:28 jjc Exp $
 */


#ifndef __SHIPINPUT__
#define __SHIPINPUT__

#include "Ship.h"


class ShipInput
{
protected:
    ShipObject	*fShip;
    float		fRoll;
    float		fYaw;
    float		fPitch;
    float		fThrust;
    float		fUp;
    float		fRight;
    bool                fLaunchBomb;
    

    void setupInput(Ship * shipRes);
    
public:
    ShipInput();

    void setShip(ShipObject *ship);
    virtual void update();
};

class ShipClientInput : public ShipInput
{
protected:
    float oldThrust;
    float oldUp;
    float oldRight;
public: 
    ShipClientInput();

    virtual void update();
    void setShipResource(Ship * shipRes);
};


#endif
