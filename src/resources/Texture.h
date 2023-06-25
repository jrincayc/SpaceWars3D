

#ifndef __TEXTURE__
#define __TEXTURE__

#include "Resource.h"
#include "GLHeaders.h"

class Texture : public Resource
{
protected:
    GLuint	fTexture[1];

public:
    Texture();
    virtual ~Texture();


    virtual bool initWithXMLNode(DOMElement *aNode);
    void bindTexture(){glBindTexture(GL_TEXTURE_2D, fTexture[0]);}

    virtual Object* createObject();

};





#endif
