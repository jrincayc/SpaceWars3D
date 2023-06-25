/*
 *  Ship.cpp
 *  SpaceWars3D
 *
 *  Created by Michael Milvich on Sun May 04 2003.
 *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ship.h"
#include "ResourceManager.h"
#include "Utility.h"
#include "Bomb.h"
#include <iostream>


ShipObject::ShipObject(Ship *ship)
{
    ResourceManager	*res = ResourceManager::getSharedManager();
    
    fShipRes = ship;
    fTexture = (Texture*)res->getResource(ship->getTextureID(), kTextureType);
    fMesh = (Mesh*)res->getResource(ship->getMeshID(), kMeshType);
    fCockpitTexture = (Texture*)res->getResource(ship->getCockpitTextureID(), kTextureType);
    fCockpitMesh = (Mesh*)res->getResource(ship->getCockpitMeshID(), kMeshType);
    fMaterial = ship->getMaterial();
    setForwardOrientation(Vector3D(0, 1, 0));
    setUpwardOrientation(Vector3D(0, 0, 1));
}

ShipObject::~ShipObject()
{
    
}

void 
ShipObject::launchBomb()
{
    float time = fUniverse->getLastValidTime();
    Vector3D location = fUniverse->getObjectLocation(time,getID());
    Vector3D velocity = fUniverse->getObjectVelocity(time,getID());
    Vector3D forward = getForwardOrientation();
    float size = 4.0f;
    Bomb * bomb = new Bomb(getID(),size,time+10.0);
    bomb->setLocation(location+forward.makeSize(size+getRadius() + 2.0));
    bomb->setVelocityVec(velocity+forward.makeSize(100.0));
    bomb->setForwardOrientation(getForwardOrientation());
    bomb->setUpwardOrientation(getUpwardOrientation());
    fUniverse->addNonPoweredObject(bomb);
    cout << "bomb launched" << endl;
}

void ShipObject::draw()
{
    //cerr << "Ship draw: " << fLocation << endl;
    fTexture->bindTexture();
    fMaterial->setGLMaterial();
    fMesh->draw();
}

void ShipObject::drawCockpit()
{
    fCockpitTexture->bindTexture();
    fMaterial->setGLMaterial();
    fCockpitMesh->draw();
}

void 
ShipObject::setUniverse(Universe * universe)
{
    fUniverse = universe;
}

Ship::Ship()
{
    fType = kShipType;
}

Ship::~Ship()
{
    delete fMaterial;
}

bool Ship::initWithXMLNode(DOMElement *aNode)
{
    XMLCh		tag[100];
    DOMElement	*element, *element2;

    if(!Resource::initWithXMLNode(aNode))
    {
        return false;
    }

    (void)XMLString::transcode("textureLink", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("id", tag, 100);
    fTextureID = XMLString::parseInt(element->getAttribute(tag));

    (void)XMLString::transcode("meshLink", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("id", tag, 100);
    fMeshID = XMLString::parseInt(element->getAttribute(tag));

    (void)XMLString::transcode("yaw", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxYaw = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fYawAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("pitch", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxPitch = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fPitchAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("roll", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxRoll = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fRollAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("thrust", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxThrust = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fThrustAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("verticalSlide", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxVertical = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fVerticalAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("horizontalSlide", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("max", tag, 100);
    fMaxHorizontal = xmlToFloat(element->getAttribute(tag));
    (void)XMLString::transcode("acc", tag, 100);
    fHorizontalAcc = xmlToFloat(element->getAttribute(tag));

    (void)XMLString::transcode("radius", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    fRadius = xmlToFloat(element->getFirstChild()->getNodeValue());

    (void)XMLString::transcode("mass", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    fMass = xmlToFloat(element->getFirstChild()->getNodeValue());

    (void)XMLString::transcode("material", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);

    fMaterial = new Material();
    fMaterial->initWithXMLNode(element);

    (void)XMLString::transcode("cockpit", tag, 100);
    element2 = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    
    (void)XMLString::transcode("textureLink", tag, 100);
    element = (DOMElement*)element2->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("id", tag, 100);
    fCockpitTextureID = XMLString::parseInt(element->getAttribute(tag));

    (void)XMLString::transcode("meshLink", tag, 100);
    element = (DOMElement*)element2->getElementsByTagName(tag)->item(0);
    (void)XMLString::transcode("id", tag, 100);
    fCockpitMeshID = XMLString::parseInt(element->getAttribute(tag));

    return true;
}

Object* Ship::createObject()
{
    ShipObject	*ship = new ShipObject(this);

    ship->setMaxForwardThrust(fMaxThrust);
    ship->setMaxUpThrust(fMaxVertical);
    ship->setMaxRightThrust(fMaxHorizontal);
    ship->setMass(fMass);
    ship->setRadius(fRadius);

    return ship;
}
