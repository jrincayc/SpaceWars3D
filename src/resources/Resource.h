

#ifndef __RESOURCE__
#define __RESOURCE__

#include <string>
#include <ostream>
#include <xercesc/dom/DOM.hpp>
#include "Object.h"

using namespace std;
using namespace xercesc;

enum ResourceTypes {kPlanetType = 10, kSunType, kSolarMapType, kTextureType, kMeshType, kShipType};

class Resource;

class ResObject : public Object
{
protected:
    Resource	*fRes;

public:
    ResObject(Resource *res);
    virtual ~ResObject();

    Resource* getResource() {return fRes;}

    virtual uint getResourceID();
    virtual uint getTypeID();
};

class Resource
{
protected:
    int		fID;
    int		fType;
    string	fName;

public:

    static Resource* createResourceOfType(string type);
    static int typeForString(string type);
        
    Resource();
    virtual ~Resource();

    int getID() {return fID;}
    int getType() {return fType;}
    string getName(){return fName;}

    virtual bool initWithXMLNode(DOMElement *aNode);

    virtual Object* createObject() = 0;

    virtual string toString();

    friend ostream& operator << (ostream &stream, Resource &res);
};

#endif
