#ifndef __LIGHT__
#define __LIGHT__

#include "Vector3D.h"
#include "GLHeaders.h"
#include <xercesc/dom/DOM.hpp>

using namespace xercesc;

class Light
{
protected:
    GLfloat	fAmbient[4];
    GLfloat	fDiffuse[4];
    GLfloat	fSpecular[4];
    GLfloat	fLocation[4];
    GLenum	fLightID;

public:
    Light();
    virtual ~Light();

    void setAmbientLight(float red, float green, float blue, float alpha)
    {
        fAmbient[0] = red; fAmbient[1] = green; fAmbient[2] = blue; fAmbient[3] = alpha;
    }
    void setDiffuseLight(float red, float green, float blue, float alpha)
    {
        fDiffuse[0] = red; fDiffuse[1] = green; fDiffuse[2] = blue; fDiffuse[2] = alpha;
    }
    void setSpecularLight(float red, float green, float blue, float alpha)
    {
        fSpecular[0] = red; fSpecular[1] = green; fSpecular[2] = blue; fSpecular[2] = alpha;
    }
    void setLocation(Vector3D loc)
    {
        fLocation[0] = loc[0]; fLocation[1] = loc[1]; fLocation[2] = loc[2];
    }

    virtual void doGLLightStuff();

    void enable() {glEnable(fLightID);}
    void disable() {glDisable(fLightID);}

    void setLightID(GLenum ID) {fLightID = ID;}
    GLenum getLightID() {return fLightID;}

    virtual void initWithXMLNode(DOMElement *aNode);
};




#endif
