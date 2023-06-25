#ifndef __MESH__
#define __MESH__

#include "Resource.h"
#include "GLHeaders.h"

class Mesh : public Resource
{
protected:
    GLfloat			*fVertices;
    GLfloat			*fTextureCoords;
    unsigned int	*fIndices;
    int				fNumTriangles;

public:
    Mesh();
    virtual ~Mesh();

    virtual bool initWithXMLNode(DOMElement *aNode);

    virtual void draw();

    virtual Object* createObject() {return NULL;}
};




#endif
