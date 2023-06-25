#include "ResourceManager.h"
#include "Preferences.h"
#include <iostream>
#include <sstream>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "DirectoryIterator.h"
#include "Sun.h"

ResourceManager	*gResourceManager = NULL;

ResourceManager* ResourceManager::getSharedManager()
{
    if(gResourceManager == NULL)
    {
        gResourceManager = new ResourceManager();
    }

    return gResourceManager;
}

ResourceManager::ResourceManager()
{
    
}

bool ResourceManager::init()
{
    Preferences		*prefs = Preferences::getSharedPreferences();
    vector<string>	paths = prefs->getResourcePaths();
    vector<string>::iterator	iter = paths.begin();

    while(iter != paths.end())
    {
        loadFromFolder(*iter + "/tags");
        iter++;
    }
    
    
    return true;
}

Resource* ResourceManager::getResource(int ID, int type)
{
    map<int, map<int, Resource*> >::iterator	resources = fResources.find(type);
    map<int, Resource*>::iterator				resource;

    if(resources != fResources.end())
    {
        resource = resources->second.find(ID);
        if(resource != resources->second.end())
        {
            return resource->second;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

vector<Resource*>* ResourceManager::getResourcesOfType(int type)
{
    vector<Resource*>	*result = new vector<Resource*>;
    map<int, map<int, Resource*> >::iterator	resources = fResources.find(type);
    map<int, Resource*>::iterator				resource;

    if(resources != fResources.end())
    {
        for(resource = resources->second.begin(); resource != resources->second.end(); ++resource)
        {
            result->push_back(resource->second);
        }
    }

    return result;
}

void ResourceManager::loadFromFolder(string path)
{
    DirectoryIterator	iter(path, "xml");

    while(iter.hasNext())
    {
        if(iter.isDir())
        {
            loadFromFolder(iter.next());
        }
        else
        {
            loadFile(iter.next());
        }
    }
}

void ResourceManager::loadFile(string path)
{
    ErrorHandler	*errHandler = (ErrorHandler*) new HandlerBase();
    DOMDocument		*doc;
    DOMElement		*root;
    DOMNodeList		*children;
    
    XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSParser* parser = ((DOMImplementationLS*)impl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

    cout << path << endl;

    if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMValidate, true))
      parser->getDomConfig()->setParameter(XMLUni::fgDOMValidate, true);
    if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMElementContentWhitespace, false))
      parser->getDomConfig()->setParameter(XMLUni::fgDOMElementContentWhitespace, false);


    // lets see if we can read this thing...
    try
    {
        doc = parser->parseURI(path.c_str());
    }
    catch(const XMLException &e)
    {
        // guess not
        char *msg = XMLString::transcode(e.getMessage());
        cerr << "Failed to read in " << path << " because: " << msg << endl;
        XMLString::release(&msg);
        return;
    }
    catch(const DOMException &e)
    {
        // guess not
        char *msg = XMLString::transcode(e.msg);
        cerr << "Failed to read in " << path << " because: " << msg << endl;
        XMLString::release(&msg);
        return;
    }
    catch(...)
    {
        cerr << "Failed to read in " << path << " do to some unkown problem parsing the xml file" << endl;
        return;
    }

    root = doc->getDocumentElement();
    children = root->getChildNodes();

    cout << "Num Tags: " << root->getChildNodes()->getLength() << endl;

    for(XMLSize_t i = 0; i < children->getLength(); i++)
    {
        loadTag((DOMElement*)children->item(i));
    }

    delete parser;
    delete errHandler;
}

void ResourceManager::loadTag(DOMElement *element)
{
    const XMLCh *name = element->getNodeName();
    char		*cName = XMLString::transcode(name);
    Resource	*res;

    res = Resource::createResourceOfType(cName);

    if(res == NULL)
    {
        cerr << "Unknown tag name: " << cName << endl;
    }

    if(res != NULL && res->initWithXMLNode(element))
    {
        fResources[res->getType()][res->getID()] = res;
    }
    else
    {
        cerr << "Failed to load tag: " << cName << endl;
    }
    XMLString::release(&cName);
}


ostream& operator << (ostream &stream, ResourceManager &res)
{
    map<int, map<int, Resource*> >::iterator	typeIter;
    map<int, Resource*>::iterator				resIter;

    for(typeIter = res.fResources.begin(); typeIter != res.fResources.end(); ++typeIter)
    {
        cout << "Resources of type: " << typeIter->first << endl;
        for(resIter = typeIter->second.begin(); resIter != typeIter->second.end(); ++resIter)
        {
            cout << *(resIter->second) << endl;
        }
    }
    
    return stream;
}
