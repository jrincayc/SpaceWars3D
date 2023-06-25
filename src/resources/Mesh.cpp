#include "Mesh.h"
#include "Utility.h"
#include <iostream>


Mesh::Mesh()
{
    fType = kMeshType;
}

Mesh::~Mesh()
{
    delete [] fVertices;
    delete [] fTextureCoords;
    delete [] fIndices;
}

bool Mesh::initWithXMLNode(DOMElement *aNode)
{
    DOMNodeList	*elements;
    XMLCh		tag[100];
    int			count;
    DOMElement	*element;
    XMLCh		x[2];
    XMLCh		y[2];
    XMLCh		z[2];
    XMLCh		u[2];
    XMLCh		v[2];
    XMLCh		v1[3];
    XMLCh		v2[3];
    XMLCh		v3[3];
    GLfloat		*vertexPtr, *textPtr;
    int			i;
    unsigned int	*indicesPtr;

    if(!Resource::initWithXMLNode(aNode))
    {
        return false;
    }

    (void)XMLString::transcode("x", x, 2);
    (void)XMLString::transcode("y", y, 2);
    (void)XMLString::transcode("z", z, 2);
    (void)XMLString::transcode("u", u, 2);
    (void)XMLString::transcode("v", v, 2);
    (void)XMLString::transcode("v1", v1, 3);
    (void)XMLString::transcode("v2", v2, 3);
    (void)XMLString::transcode("v3", v3, 3);

    (void)XMLString::transcode("v", tag, 100);
    elements = aNode->getElementsByTagName(tag);

    count = elements->getLength();

    fVertices = new GLfloat[3 * count];
    fTextureCoords = new GLfloat[2 * count];

    for(vertexPtr = fVertices, textPtr = fTextureCoords, i = 0; i < count; i++, vertexPtr += 3, textPtr += 2)
    {
        element = (DOMElement*)elements->item(i);
        vertexPtr[0] = xmlToFloat(element->getAttribute(x));
        vertexPtr[1] = xmlToFloat(element->getAttribute(y));
        vertexPtr[2] = xmlToFloat(element->getAttribute(z));

        textPtr[0] = xmlToFloat(element->getAttribute(u));
        textPtr[1] = xmlToFloat(element->getAttribute(v));
    }

    (void)XMLString::transcode("t", tag, 100);
    elements = aNode->getElementsByTagName(tag);

    fNumTriangles = elements->getLength();

    fIndices = new unsigned int[3 * fNumTriangles];

    for(indicesPtr = fIndices, i = 0; i < fNumTriangles; i++, indicesPtr += 3)
    {
        element = (DOMElement*)elements->item(i);
        indicesPtr[0] = XMLString::parseInt(element->getAttribute(v1));
        indicesPtr[1] = XMLString::parseInt(element->getAttribute(v2));
        indicesPtr[2] = XMLString::parseInt(element->getAttribute(v3));
    }

    return true;
}

void Mesh::draw()
{
    glVertexPointer(3, GL_FLOAT, 0, fVertices);
    glTexCoordPointer(2, GL_FLOAT, 0, fTextureCoords);
    glDrawElements(GL_TRIANGLES, fNumTriangles * 3, GL_UNSIGNED_INT, fIndices);
}
