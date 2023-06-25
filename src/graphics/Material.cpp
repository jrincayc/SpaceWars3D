
#include "Material.h"
#include "Utility.h"


Material::Material()
{
    
}

Material::~Material()
{
    
}

void Material::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    fAmbient[0] = r;
    fAmbient[1] = g;
    fAmbient[2] = b;
    fAmbient[3] = a;
}

void Material::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    fDiffuse[0] = r;
    fDiffuse[1] = g;
    fDiffuse[2] = b;
    fDiffuse[3] = a;
}

void Material::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    fSpecular[0] = r;
    fSpecular[1] = g;
    fSpecular[2] = b;
    fSpecular[3] = a;
}

void Material::setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    fEmission[0] = r;
    fEmission[1] = g;
    fEmission[2] = b;
    fEmission[3] = a;
}

void Material::setShininess(GLfloat shiny)
{
    fShininess = shiny;
}

void Material::setGLMaterial()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, fAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, fDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, fEmission);
    glMaterialf(GL_FRONT, GL_SHININESS, fShininess);
}

void Material::initWithXMLNode(DOMElement *aNode)
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

    (void)XMLString::transcode("emissionLight", tag, 100);
    element = (DOMElement*)aNode->getElementsByTagName(tag)->item(0);
    colorFromXML(element, fEmission);

    (void)XMLString::transcode("shininess", tag, 100);
    fShininess = xmlToFloat(aNode->getElementsByTagName(tag)->item(0)->getFirstChild()->getNodeValue());
}
