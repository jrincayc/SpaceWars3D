

#include "ShipInput.h"
#include "PlayerInput.h"
#include <iostream>
#include <math.h>

ShipInput::ShipInput()
{

    fThrust = fRight = fUp = fRoll = fYaw = fPitch = 0;
    fLaunchBomb = false;
}

void ShipInput::setShip(ShipObject *ship)
{
    fShip = ship;
    Ship	*shipRes = (Ship*)fShip->getResource();
    setupInput(shipRes);
}
void ShipInput::setupInput(Ship * shipRes)
{
    PlayerInput	*inputManager = PlayerInput::getSharedInput();
    Input	*input;
    float	acc, max;

    acc = shipRes->getThrustAcc();
    input = new AcceleratedInput(&fThrust, -1.0, 1.0, 0.0, acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('g', input));
    input = new AcceleratedInput(&fThrust, -1.0, 1.0, 0.0, -acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('h', input));

    acc = shipRes->getVerticalAcc();
    cout << acc;
    input = new AcceleratedInput(&fUp, -1.0, 1.0, 0.0, acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('f', input));
    input = new AcceleratedInput(&fUp, -1.0, 1.0, 0.0, -acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('d', input));

    acc = shipRes->getHorizontalAcc();
    cout << acc;
    input = new AcceleratedInput(&fRight, -1.0, 1.0, 0.0, acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('m', input));
    input = new AcceleratedInput(&fRight, -1.0, 1.0, 0.0, -acc, 1.0, -1.0);
    inputManager->addInput(new KeyInput('b', input));

    acc = shipRes->getPitchAcc();
    max = shipRes->getMaxPitch();
    input = new AcceleratedInput(&fPitch, -max, max, 0.0, acc, max, -max);
    inputManager->addInput(new KeyInput(SDLK_DOWN, input));
    input = new AcceleratedInput(&fPitch, -max, max, 0.0, -acc, max, -max);
    inputManager->addInput(new KeyInput(SDLK_UP, input));

    acc = shipRes->getYawAcc();
    max = shipRes->getMaxYaw();
    input = new AcceleratedInput(&fYaw, -max, max, 0.0, -acc, max, -max);
    inputManager->addInput(new KeyInput(SDLK_RIGHT, input));
    input = new AcceleratedInput(&fYaw, -max, max, 0.0, acc, max, -max);
    inputManager->addInput(new KeyInput(SDLK_LEFT, input));

    acc = shipRes->getRollAcc();
    max = shipRes->getMaxRoll();
    input = new AcceleratedInput(&fRoll, -max, max, 0.0, acc, max, -max);
    inputManager->addInput(new KeyInput('v', input));
    input = new AcceleratedInput(&fRoll, -max, max, 0.0, -acc, max, -max);
    inputManager->addInput(new KeyInput('z', input));
    
    inputManager->addInput(new KeyInput(' ',new ToggleInput(&fLaunchBomb))); 
    
}

void ShipInput::update()
{
    if(fShip != NULL)
    {
        fShip->setRightThrustPercent(fRight);
        fShip->setUpThrustPercent(fUp);
        fShip->setForwardThrustPercent(fThrust);

	fShip->pitch(fPitch * .16);
	fShip->yaw(fYaw * .16);
	fShip->roll(fRoll * .16);
	if(fLaunchBomb) 
	{
	    fLaunchBomb=false;
	    fShip->launchBomb();
	}
    }
}

ShipClientInput::ShipClientInput()
{

    fThrust = fRight = fUp = fRoll = fYaw = fPitch = 0;
    oldThrust = oldUp = oldRight = 0;
    fLaunchBomb = false;
}


void ShipClientInput::update() 
{
    if(oldThrust != fThrust) {
	cout << "forward_thrust " << fThrust << endl;
	oldThrust = fThrust;
    }
    if(oldRight != fRight) {
	cout << "right_thrust " << fRight << endl;
	oldRight = fRight;
    }
    if(oldUp != fUp) {
	cout << "up_thrust " << fUp << endl;
	oldUp = fUp;
    }
    if(fYaw != 0.0) {
	cout << "yaw " << fYaw * .16<< endl;
    }
    if(fPitch != 0.0) {
	cout << "pitch " << fPitch * .16 << endl;
    }
    if(fRoll != 0.0) {
	cout << "roll " << fRoll * .16 << endl;
    }
    if(fLaunchBomb) {
	fLaunchBomb=false;
	cout << "launch_bomb" << endl;
    }
}

void ShipClientInput::setShipResource(Ship * shipRes) {
    setupInput(shipRes);

}
