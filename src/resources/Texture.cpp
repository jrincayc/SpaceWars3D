#include "Texture.h"
#include <stdio.h>
#include <iostream>
#include "Preferences.h"

Texture::Texture()
{
    fType = kTextureType;
}

Texture::~Texture()
{
    
}

bool Texture::initWithXMLNode(DOMElement *aNode)
{
    char	temp[256];
    XMLCh	tag[100];
    int		width, height;
    FILE	*file;
    char	*buffer;
    string	resPath = Preferences::getSharedPreferences()->getResourcePaths()[0] + "/textures/";
    
    if(!Resource::initWithXMLNode(aNode))
    {
        return false;
    }

    (void)XMLString::transcode("width", tag, 100);
    width = XMLString::parseInt(aNode->getAttribute(tag));

    (void)XMLString::transcode("height", tag, 100);
    height = XMLString::parseInt(aNode->getAttribute(tag));
    
    (void)XMLString::transcode("path", tag, 100);
    XMLString::transcode(aNode->getAttribute(tag), temp, 255);

    resPath += temp;

    file = fopen(resPath.c_str(), "r");
    if(file == NULL)
    {
        cout << "Can't open file: " << resPath << endl;
        return false;
    }

    buffer = (char*)malloc(width * height * 3);
    fread(buffer, width * height * 3, 1, file);

    glGenTextures(1, &fTexture[0]);
    glBindTexture(GL_TEXTURE_2D, fTexture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

    free(buffer);

    return true;
}

Object* Texture::createObject()
{
    cout << "createObject should have never been called on a texture... probably going to crash here. " << endl;
    return NULL;
}
