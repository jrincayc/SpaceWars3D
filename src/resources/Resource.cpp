#include "Resource.h"
#include "Sun.h"
#include "Planet.h"
#include "SolarMap.h"
#include "Texture.h"
#include "Mesh.h"
#include "Ship.h"
#include <sstream>
#include <xercesc/util/XMLString.hpp>


ResObject::ResObject(Resource *res)
{
    fRes = res;
}

ResObject::~ResObject()
{
    
}

uint ResObject::getResourceID()
{
    return (uint)fRes->getType();
}

uint ResObject::getTypeID()
{
    return (uint)fRes->getID();
}

Resource* Resource::createResourceOfType(string type)
{
    if(type == "sun")
    {
        return new Sun();
    }
    else if(type == "planet")
    {
        return new Planet();
    }
    else if(type == "solarMap")
    {
        return new SolarMap();
    }
    else if(type == "texture")
    {
        return new Texture();
    }
    else if(type == "mesh")
    {
        return new Mesh();
    }
    else if(type == "ship")
    {
        return new Ship();
    }
    else
    {
        return NULL;
    }
}

int Resource::typeForString(string type)
{
    if(type == "sun")
    {
        return kSunType;
    }
    else if(type == "planet")
    {
        return kPlanetType;
    }
    else if(type == "solarMap")
    {
        return kSolarMapType;
    }
    else if(type == "texture")
    {
        return kTextureType;
    }
    else if(type == "mesh")
    {
        return kMeshType;
    }
    else if(type == "ship")
    {
        return kShipType;
    }
    else
    {
        return -1;
    }
}

Resource::Resource()
{
    fID = fType = 0;
}

Resource::~Resource()
{
    
}

bool Resource::initWithXMLNode(DOMElement *aNode)
{
    const XMLCh		*ID, *name;
    char			cName[256];

    // get the attributes
    ID = aNode->getAttribute(XMLString::transcode("id"));
    name = aNode->getAttribute(XMLString::transcode("name"));

    // check to make sure they were defined
    if(XMLString::stringLen(ID) > 0 && XMLString::stringLen(name) > 0)
    {
        fID = XMLString::parseInt(ID);

        // convert from a XMLCh to a char
        if(! XMLString::transcode(name, cName, 255))
        {
            return false;
        }
        fName = cName;
    }
    else
    {
        return false;
    }

    return true;
}

string Resource::toString()
{
    stringstream	stream;

    stream << " ID = " << fID;
    stream << " Type = " << fType;
    stream << " Name = \"" << fName << "\"";

    return stream.str();
}

ostream& operator << (ostream &stream, Resource &res)
{
    stream << res.toString();
    return stream;
}
