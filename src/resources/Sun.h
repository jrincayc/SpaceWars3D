#ifndef __SUN__
#define __SUN__

#include "Resource.h"
#include "Planet.h"
#include "Light.h"

class Sun;

class SunObject : public PlanetObject
{
protected:
public:
    SunObject(Sun *res);
    virtual ~SunObject();

    virtual void addedToUniverse();
    virtual void prepareToDraw();
};


class Sun : public Planet
{
protected:
    Light	*fLight;
    
public:
    Sun();
    virtual ~Sun();

    virtual bool initWithXMLNode(DOMElement *aNode);
    
    virtual Object* createObject();

    Light* getLight() {return fLight;}
};

#endif
