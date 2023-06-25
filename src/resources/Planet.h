#ifndef __PLANET__
#define __PLANET__

#include "Resource.h"
#include "Object.h"
#include "Material.h"

class Planet;

class PlanetObject : public ResObject
{
protected:
    float fRotation;
public:
    PlanetObject(Planet *res);
    virtual ~PlanetObject();
    
    virtual void updateTime(float currentTime, float deltaTime);

    virtual void draw();
};

class Planet : public Resource
{
public:
    float		fRadius;
    float		fMass;
    int			fTextureID;
    Material	*fMaterial;
    float		fRotation;

public:
    Planet();
    virtual ~Planet();

    virtual bool initWithXMLNode(DOMElement *aNode);

    float getRadius() {return fRadius;}
    float getMass() {return fMass;}
    float getRotation() {return fRotation;}
    Material* getMaterial() {return fMaterial;}
    
    virtual void draw(PlanetObject *object);


    virtual string toString();

    virtual Object* createObject();
};

#endif
