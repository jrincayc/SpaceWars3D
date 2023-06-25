#ifndef __SOLARMAP__
#define __SOLARMAP__

#include "Resource.h"
#include <vector>
#include "Vector3D.h"
#include "Universe.h"

typedef struct 
{
    int			type;
    int			ID;
    Vector3D	location;
    Vector3D	velocity;
    Vector3D	forwardOrientation;
    Vector3D	upwardOrientation;
} sSpaceObject;

class SolarMap : public Resource
{
protected:
    vector<sSpaceObject>	fGravObjects;

public:
    SolarMap();
    virtual ~SolarMap();

    virtual bool initWithXMLNode(DOMElement *aNode);

    virtual bool populateUniverse(Universe *universe);

    virtual Object* createObject();

protected:
    void parseGravObject(DOMElement *gravObject);
};

#endif
