#include "Planet.h"
#include "Utility.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include "GLHeaders.h"
#include "Texture.h"
#include "ResourceManager.h"

using namespace std;


PlanetObject::PlanetObject(Planet *res) : ResObject(res)
{
    fRotation = ((Planet*)res)->getRotation();
}

PlanetObject::~PlanetObject()
{

}

void PlanetObject::draw()
{
    ((Planet*)fRes)->draw(this);
}

void PlanetObject::updateTime(float currentTime, float deltaTime)
{
    rotate(getUpwardOrientation(), deltaTime * fRotation);
}


Planet::Planet()
{
    fType = kPlanetType;
}

Planet::~Planet()
{
    delete fMaterial;
}

bool Planet::initWithXMLNode(DOMElement *aNode)
{
    XMLCh		tag[100];
    DOMElement	*element;
    
    if(!Resource::initWithXMLNode(aNode))
    {
        return false;
    }

    XMLString::transcode("rotation", tag, 100);
    fRotation = xmlToFloat(aNode->getElementsByTagName(tag)->item(0)->getFirstChild()->getNodeValue());

    XMLString::transcode("mass", tag, 100);
    fMass = xmlToFloat(aNode->getElementsByTagName(tag)->item(0)->getFirstChild()->getNodeValue());

    XMLString::transcode("radius", tag, 100);
    fRadius = xmlToFloat(aNode->getElementsByTagName(tag)->item(0)->getFirstChild()->getNodeValue());

    (void)XMLString::transcode("textureLink", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);

    (void)XMLString::transcode("id", tag, 100);
    fTextureID = XMLString::parseInt(element->getAttribute(tag));

    (void)XMLString::transcode("material", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);

    fMaterial = new Material();
    fMaterial->initWithXMLNode(element);
    
    return true;
}

void Planet::draw(PlanetObject *object)
{
    fMaterial->setGLMaterial();
    ((Texture*)ResourceManager::getSharedManager()->getResource(fTextureID, kTextureType))->bindTexture();
    drawSphere(fRadius, 25);
}

string Planet::toString()
{
    stringstream	stream;

    stream << Resource::toString()
        << " Radius: " << fRadius
        << " Mass: " << fMass;

    return stream.str();
}

Object* Planet::createObject()
{
    PlanetObject	*object = new PlanetObject(this);

    object->setMass(fMass);
    object->setRadius(fRadius);

    return object;
}
