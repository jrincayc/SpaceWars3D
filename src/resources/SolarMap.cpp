#include "SolarMap.h"
#include "Utility.h"
#include "Object.h"
#include "ResourceManager.h"

#include <iostream>

SolarMap::SolarMap()
{
    fType = kSolarMapType;
}

SolarMap::~SolarMap()
{
    
}

bool SolarMap::initWithXMLNode(DOMElement *aNode)
{
    DOMNodeList		*children;
    XMLCh			tag[100];

    if(!Resource::initWithXMLNode(aNode))
    {
        return false;
    }

    // first read in the grav objects
    XMLString::transcode("gravList", tag, 100);
    children = aNode->getElementsByTagName(tag)->item(0)->getChildNodes();
    for(unsigned int i = 0; i < children->getLength(); i++)
    {
        parseGravObject((DOMElement*)children->item(i));
    }

    return true;
}

void SolarMap::parseGravObject(DOMElement *gravObject)
{
    XMLCh			tag[100];
    DOMElement		*element;
    sSpaceObject	object;
    char			temp[100];

    // read in the link stuff
    XMLString::transcode("link", tag, 100);
    element = (DOMElement*)gravObject->getElementsByTagName(tag)->item(0);
    XMLString::transcode("id", tag, 100);
    object.ID = XMLString::parseInt(element->getAttribute(tag));
    XMLString::transcode("type", tag, 100);
    XMLString::transcode(element->getAttribute(tag), temp, 100);
    object.type = Resource::typeForString(temp);
    
    // then the location
    XMLString::transcode("location", tag, 100);
    object.location = vectorFromXML((DOMElement*)gravObject->getElementsByTagName(tag)->item(0));

    // velocity
    XMLString::transcode("velocity", tag, 100);
    object.velocity = vectorFromXML((DOMElement*)gravObject->getElementsByTagName(tag)->item(0));

    // forwardOrientation
    XMLString::transcode("forwardOrientation", tag, 100);
    object.forwardOrientation = vectorFromXML((DOMElement*)gravObject->getElementsByTagName(tag)->item(0));

    // upwardOrientation
    XMLString::transcode("upwardOrientation", tag, 100);
    object.upwardOrientation = vectorFromXML((DOMElement*)gravObject->getElementsByTagName(tag)->item(0));


    fGravObjects.push_back(object);
}


bool SolarMap::populateUniverse(Universe *universe)
{
    vector<sSpaceObject>::iterator	iter = fGravObjects.begin();
    sSpaceObject					spaceObject;
    Object							*object;
    Resource						*res;
    ResourceManager					*resManager = ResourceManager::getSharedManager();
    

    while(iter != fGravObjects.end())
    {
        spaceObject = *iter;

        res = resManager->getResource(spaceObject.ID, spaceObject.type);
        if(res == NULL)
        {
            cerr << "Failed to find resource " << spaceObject.ID << " of type " << spaceObject.type << endl;
            return false;
        }

        object = res->createObject();

        object->setLocation(spaceObject.location);
        object->setVelocityVec(spaceObject.velocity);
        object->setForwardOrientation(spaceObject.forwardOrientation);
        object->setUpwardOrientation(spaceObject.upwardOrientation);

        universe->addGravitationalObject(object);

        iter++;
    }

    return true;
}

Object* SolarMap::createObject()
{
    cerr << "hmm... someone tried to create an object from a solor map. This is a bad thing, and you will probably crash soon, cause we will return NULL" << endl;

    return NULL;
}
