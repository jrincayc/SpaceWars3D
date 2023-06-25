#ifndef __MATERIAL__
#define __MATERIAL__


#include "Vector3D.h"
#include "GLHeaders.h"
#include <xercesc/dom/DOM.hpp>

using namespace xercesc;

class Material
{
protected:
    GLfloat		fAmbient[4];
    GLfloat		fDiffuse[4];
    GLfloat		fSpecular[4];
    GLfloat		fEmission[4];
    GLfloat		fShininess;

public:
    Material();
    virtual ~Material();

    void setGLMaterial();

    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setShininess(GLfloat shiny);

    virtual void initWithXMLNode(DOMElement *aNode);
};


#endif
