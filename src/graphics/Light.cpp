#include "Light.h"
#include "Utility.h"

Light::Light()
{
    for(int i = 0; i < 4; i++)
    {
        fAmbient[0] = fLocation[0] = fDiffuse[0] = fSpecular[0];
    }
}

Light::~Light()
{
    
}

void Light::doGLLightStuff()
{
    glLightfv(fLightID, GL_POSITION, fLocation);
    glLightfv(fLightID, GL_AMBIENT, fAmbient);
    glLightfv(fLightID, GL_DIFFUSE, fDiffuse);
    glLightfv(fLightID, GL_SPECULAR, fSpecular);
}

void Light::initWithXMLNode(DOMElement *aNode)
{
    XMLCh		tag[100];
    DOMElement	*element;

    (void)XMLString::transcode("ambientLight", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    colorFromXML(element, fAmbient);

    (void)XMLString::transcode("diffuseLight", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    colorFromXML(element, fDiffuse);

    (void)XMLString::transcode("specularLight", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    colorFromXML(element, fSpecular);
}
