#include "Utility.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include "GLHeaders.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int strInsensitiveCompare(string str1, string str2)
{
    // convert to lower case
    for(unsigned int i = 0; i < str1.length(); i++)
    {
        str1[i] = tolower(str1[i]);
    }
    for(unsigned int i = 0; i < str2.length(); i++)
    {
        str2[i] = tolower(str2[i]);
    }

    return str1.compare(str2);
}

bool pathHasExtension(const string &path, const string &extension)
{
    int	extLength = extension.length();

    if(path[path.length() - 1 - extLength] != '.')
    {
        return false;
    }
    else
    {
        return strInsensitiveCompare(path.substr(path.length() - extLength, extLength), extension) == 0;
    }
}

Vector3D vectorFromXML(DOMElement* node)
{
    XMLCh *keyX = XMLString::transcode("x");
    XMLCh *keyY = XMLString::transcode("y");
    XMLCh *keyZ = XMLString::transcode("z");
    char *sx = XMLString::transcode(node->getAttribute(keyX));
    char *sy = XMLString::transcode(node->getAttribute(keyY));
    char *sz = XMLString::transcode(node->getAttribute(keyZ));
    float	x, y, z;
    Vector3D	vec;

    x = y = z = 0;

    sscanf(sx, "%f", &x);
    sscanf(sy, "%f", &y);
    sscanf(sz, "%f", &z);

    vec[0] = x;
    vec[1] = y;
    vec[2] = z;

    XMLString::release(&keyX);
    XMLString::release(&keyY);
    XMLString::release(&keyZ);
    XMLString::release(&sx);
    XMLString::release(&sy);
    XMLString::release(&sz);

    return vec;
}

float xmlToFloat(const XMLCh *string)
{
    char 	*cString = XMLString::transcode(string);
    float	temp = 0.0;

    sscanf(cString, "%f", &temp);

    XMLString::release(&cString);

    return temp;
}

GLUquadric	*gSphereQuad = NULL;
void drawSphere(float radius, int pres)
{
    if(gSphereQuad == NULL)
    {
        gSphereQuad = gluNewQuadric();
        gluQuadricTexture(gSphereQuad, GL_TRUE);
    }
    gluSphere(gSphereQuad, radius, pres, pres);
}

void colorFromXML(DOMElement *node, GLfloat color[])
{
    XMLCh	tag[100];

    (void)XMLString::transcode("red", tag, 100);
    color[0] = xmlToFloat(node->getAttribute(tag));

    (void)XMLString::transcode("green", tag, 100);
    color[1] = xmlToFloat(node->getAttribute(tag));

    (void)XMLString::transcode("blue", tag, 100);
    color[2] = xmlToFloat(node->getAttribute(tag));

    (void)XMLString::transcode("alpha", tag, 100);
    color[3] = xmlToFloat(node->getAttribute(tag));
}


float randomFloat()
{
    static bool	seeded = false;
    
    if(!seeded)
    {
        srandom((unsigned int)time(NULL));
	seeded = true;
    }
    
    return (float)random() / (float)RAND_MAX;
}
