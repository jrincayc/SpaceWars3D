#include "PointLight.h"


PointLight::PointLight()
{
    fLocation[3] = 1;
}

PointLight::~PointLight()
{
    
}

void PointLight::initWithXMLNode(DOMElement *aNode)
{
    Light::initWithXMLNode(aNode);
    fLocation[0] = fLocation[1] = fLocation[2] = 0;
    fLocation[3] = 1;
}
