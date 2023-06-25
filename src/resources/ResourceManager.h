

#ifndef __RESOURCEMANAGER__
#define __RESOURCEMANAGER__

#include "Resource.h"
#include <map>
#include <vector>
#include <string>
#include <ostream>
#include <xercesc/dom/DOM.hpp>

using namespace std;

class ResourceManager
{
protected:
    map<int, map<int, Resource*> >	fResources;

public:
    static ResourceManager* getSharedManager();

    ResourceManager();

    bool init();
    
    Resource* getResource(int ID, int type);
    vector<Resource*>* getResourcesOfType(int type);

    friend ostream& operator << (ostream &stream, ResourceManager &res);

protected:
    void loadFromFolder(string path);
    void loadFile(string path);
    void loadTag(DOMElement* element);
};

#endif
