#include "Camera.h"
#include "GLHeaders.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

// for converting degrees to radians
const float kDegreesToRadians = .01745329252;

Camera::Camera(void)
{
    set(Point3D(0.0, 0.0, 20.0), Vector3D(0.0, 0.0, -1.0), Vector3D(0.0, 1.0, 0.0));
    setShape(40.0, 1.0);
    setNear(5);
    setFar(500);
    setUpMatrix();
    setUpControls();
    setMode(kGlobal);

    fRollInput = fPitchInput = fYawInput = fVertSlideInput = fHorzSlideInput = fForwardInput = 0.0;
}

void Camera::set(const Point3D &location, const Vector3D &direction, const Vector3D &up)
{
    fLocVec = location;
    
    // fN is the direction we are looking, in open gl, the "z" axis sticks out of the screen
    // so if they are looking along the direction vector, then z is the oposite vector
    fN = -direction;
    
    // the fU vector is a cross between the up and the fN... it should be pointing to the "right"
    fU = up.cross(fN);
    
    // normal vectors are nice
    fU.normalize();
    fN.normalize();
    
    // the fV vector is a cross between fN, and fU... we don't use the up vector since it only has
    // to be in the right plane, but not perpendicular to fU.
    fV = fN.cross(fU);
    
    // finaly update our copy of the model matrix
    setUpMatrix();
}

void Camera::roll(const float &angle)
{
    float	cs = cos(angle * kDegreesToRadians);
    float	sn = sin(angle * kDegreesToRadians);
    Vector3D	savedU = fU;
    
	// updating the fU and fV vector since they get rotated by this evil equation
    fU.set(cs * fU[0] - sn * fV[0], cs * fU[1] - sn * fV[1], cs * fU[2] - sn * fV[2]);
    fV.set(sn * savedU[0] + cs * fV[0], sn * savedU[1] + cs * fV[1], sn * savedU[2] + cs * fV[2]);
    setUpMatrix();
}

void Camera::pitch(const float &angle)
{
    float	cs = cos(angle * kDegreesToRadians);
    float	sn = sin(angle * kDegreesToRadians);
    Vector3D	savedN = fN;
    
	// fN and fV get updated this time
    fN.set(cs * fN[0] - sn * fV[0], cs * fN[1] - sn * fV[1], cs * fN[2] - sn * fV[2]);
    fV.set(sn * savedN[0] + cs * fV[0], sn * savedN[1] + cs * fV[1], sn * savedN[2] + cs * fV[2]);
    setUpMatrix();
}

void Camera::yaw(const float &angle)
{
    float	cs = cos(angle * kDegreesToRadians);
    float	sn = sin(angle * kDegreesToRadians);
    Vector3D	savedN = fN;
    
	// fN and fU are updated this time
    fN.set(cs * fN[0] - sn * fU[0], cs * fN[1] - sn * fU[1], cs * fN[2] - sn * fU[2]);
    fU.set(sn * savedN[0] + cs * fU[0], sn * savedN[1] + cs * fU[1], sn * savedN[2] + cs * fU[2]);
    setUpMatrix();
}

void Camera::slide(const Vector3D &vec)
{
    Vector3D	us = fU.makeSize(-vec[0]);
    Vector3D	vs = fV.makeSize(-vec[1]);
    Vector3D	ns = fN.makeSize(-vec[2]);

    Vector3D	x(1,0,0);
    Vector3D	y(0,1,0);
    Vector3D	z(0,0,1);
    
    fLocVec[0] += us.dot(x) + vs.dot(x) + ns.dot(x);
    fLocVec[1] += us.dot(y) + vs.dot(y) + ns.dot(y);
    fLocVec[2] += us.dot(z) + vs.dot(z) + ns.dot(z);
    setUpMatrix();
}


void Camera::setShape(const float &vAngle, const float &aspectRatio)
{
    fViewAngle = vAngle;
    fAspectRatio = aspectRatio;
}

void Camera::setNear(const float &near)
{
    fNear = near;
}

void Camera::setFar(const float &far)
{
    fFar = far;
}

void Camera::updateGLCamera()
{
    float	matrix[16];

    readControls();
    
    // set up the perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fViewAngle, fAspectRatio, fNear, fFar);
    
    // copy our model matrix to opengl
    fModelMatrix.getFlatMatrix(matrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(matrix);
}

void Camera::setUpMatrix()
{
    fModelMatrix(0,0) = fU[0];
    fModelMatrix(1,0) = fV[0];
    fModelMatrix(2,0) = fN[0];
    fModelMatrix(3,0) = 0;
    
    fModelMatrix(0,1) = fU[1];
    fModelMatrix(1,1) = fV[1];
    fModelMatrix(2,1) = fN[1];
    fModelMatrix(3,1) = 0;
    
    fModelMatrix(0,2) = fU[2];
    fModelMatrix(1,2) = fV[2];
    fModelMatrix(2,2) = fN[2];
    fModelMatrix(3,2) = 0;
    
    fModelMatrix(0,3) = fLocVec.dot(fU);
    fModelMatrix(1,3) = fLocVec.dot(fV);
    fModelMatrix(2,3) = fLocVec.dot(fN);
    fModelMatrix(3,3) = 1;
}

void Camera::setUpControls()
{
    Input	*input;
    PlayerInput			*inputManager = PlayerInput::getSharedInput();

    input = new AcceleratedInput(&fRollInput, -M_PI, M_PI, 0.0, .05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('\'', input));
    input = new AcceleratedInput(&fRollInput, -M_PI, M_PI, 0.0, -.05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('.', input));

    input = new AcceleratedInput(&fPitchInput, -M_PI, M_PI, 0.0, -.05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('y', input));
    input = new AcceleratedInput(&fPitchInput, -M_PI, M_PI, 0.0, .05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('i', input));

    input = new AcceleratedInput(&fYawInput, -M_PI, M_PI, 0.0, -.05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('a', input));
    input = new AcceleratedInput(&fYawInput, -M_PI, M_PI, 0.0, .05, M_PI, -M_PI, true);
    inputManager->addInput(new KeyInput('e', input));

    input = new AcceleratedInput(&fForwardInput, -20, 20, 0.0, -.1, 20, -20, true);
    inputManager->addInput(new KeyInput(',', input));
    input = new AcceleratedInput(&fForwardInput, -20, 20, 0.0, .1, 20, -20, true);
    inputManager->addInput(new KeyInput('o', input));

    input = new AcceleratedInput(&fHorzSlideInput, -20, 20, 0.0, -.1, 20, -20, true);
    inputManager->addInput(new KeyInput(';', input));
    input = new AcceleratedInput(&fHorzSlideInput, -20, 20, 0.0, .1, 20, -20, true);
    inputManager->addInput(new KeyInput('q', input));

    input = new AcceleratedInput(&fVertSlideInput, -20, 20, 0.0, .1, 20, -20, true);
    inputManager->addInput(new KeyInput('p', input));
    input = new AcceleratedInput(&fVertSlideInput, -20, 20, 0.0, -.1, 20, -20, true);
    inputManager->addInput(new KeyInput('u', input));
}

void Camera::readControls()
{

    if((fMode == kChase || fMode == kCockpit) 
       && !(fCanvas->hasObject(fChaseObjectID)))
    {
        setMode(kGlobal);
        fChaseObjectID = -1;
    }
    
    switch(fMode)
    {
        case kChase:
            readControlsChase();
            break;
        case kTrail:
            readControlsTrail();
            break;
        case kCockpit:
            readControlsCockpit();
            break;
        default:
            readControlsGlobal();
            break;
    }
}

void Camera::readControlsChase()
{
    Vector3D	pos = fCanvas->getObjectLocation(fChaseObjectID);
    Vector3D	view, up;

    view = fChaseQ * Vector3D(0, -1, 0);
    up = fChaseQ * Vector3D(0, 0, 1);
    
    
    if(fYawInput != 0)
    {
        Quaternion	q(up, fYawInput * .01);
        fChaseQ = q * fChaseQ;
    }
    
    if(fRollInput != 0)
    {
        Quaternion	q(view, fRollInput * .01);
        fChaseQ = q * fChaseQ;
    }

    if(fForwardInput != 0)
    {
        Quaternion	q(view.cross(up), fForwardInput * -.005);
        fChaseQ = q * fChaseQ;
    }

    if(fVertSlideInput != 0)
    {
        fChaseDistance += fVertSlideInput * -.1;
        if(fChaseDistance < 4)
        {
            fChaseDistance = 4;
        }
    }

    view = fChaseQ * Vector3D(0, -1, 0);
    up = fChaseQ * Vector3D(0, 0, 1);

    set(-(pos + (view * fChaseDistance)), -view, up);
}

void Camera::readControlsTrail()
{
    Vector3D	pos = fCanvas->getObjectLocation(fChaseObjectID);
    Vector3D	view = 
	-fCanvas->getObject(fChaseObjectID)->getForwardOrientation();

    if(fVertSlideInput != 0)
    {
        fChaseDistance += fVertSlideInput * -.1;
        if(fChaseDistance < 4)
        {
            fChaseDistance = 4;
        }
    }
    
    set(-(pos + (view * fChaseDistance)), -view, 
	fCanvas->getObject(fChaseObjectID)->getUpwardOrientation());
}

void Camera::readControlsCockpit()
{
    Vector3D	pos = fCanvas->getObjectLocation(fChaseObjectID);
    Vector3D	view = 
	fCanvas->getObject(fChaseObjectID)->getForwardOrientation();
    
    set(-(pos + (view * .5)), view, 
	fCanvas->getObject(fChaseObjectID)->getUpwardOrientation());
}

void Camera::readControlsGlobal()
{
    if(fRollInput != 0)
    {
        roll(fRollInput);
    }
    if(fPitchInput != 0)
    {
        pitch(fPitchInput);
    }
    if(fYawInput != 0)
    {
        yaw(fYawInput);
    }
    if(fVertSlideInput != 0)
    {
        slide(Vector3D(0, fVertSlideInput, 0));
    }
    if(fHorzSlideInput != 0)
    {
        slide(Vector3D(fHorzSlideInput, 0, 0));
    }
    if(fForwardInput != 0)
    {
        slide(Vector3D(0, 0, fForwardInput));
    }
}

void Camera::setChaseObjectID(int id)
{
    fChaseDistance = 5;
    fChaseObjectID = id;
}

void Camera::setMode(int mode)
{
    fMode = mode;

    switch(fMode)
    {
        case kChase:
            fChaseQ = Quaternion();
            fChaseDistance = 5;
            break;
        case kTrail:
            fChaseDistance = 5;
            break;
        case kCockpit:
            break;
        default:
            fMode = kGlobal;
            break;
    }
}
