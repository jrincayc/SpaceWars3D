#include "Sun.h"
#include "Utility.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include "GLHeaders.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "PointLight.h"
#include "LightManager.h"

using namespace std;



SunObject::SunObject(Sun *res) : PlanetObject(res)
{
}

SunObject::~SunObject()
{
    
}

void SunObject::addedToUniverse()
{
    LightManager::getLightManager()->addLight(((Sun*)fRes)->getLight());
}

void SunObject::prepareToDraw()
{
    ((Sun*)fRes)->getLight()->setLocation(fLocation);
}


Sun::Sun()
{
    fType = kSunType;
}

Sun::~Sun()
{
    
}

bool Sun::initWithXMLNode(DOMElement *aNode)
{
    XMLCh		tag[100];
    DOMElement	*element;

    if(!Planet::initWithXMLNode(aNode))
    {
        return false;
    }

    (void)XMLString::transcode("pointLight", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);

    fLight = new PointLight();
    fLight->initWithXMLNode(element);

    return true;
}

Object* Sun::createObject()
{
    SunObject	*object = new SunObject(this);

    object->setMass(fMass);
    object->setRadius(fRadius);

    return object;
}
