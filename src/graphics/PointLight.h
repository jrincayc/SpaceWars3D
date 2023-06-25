#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    virtual ~PointLight();

    virtual void initWithXMLNode(DOMElement *aNode);
};




#endif
