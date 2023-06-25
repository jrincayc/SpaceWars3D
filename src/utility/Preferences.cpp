#include "Preferences.h"
#include <stdlib.h>

Preferences *gPrefs = NULL;


Preferences::Preferences()
{
    
}

Preferences::~Preferences()
{
    
}

Preferences* Preferences::getSharedPreferences()
{
    if(gPrefs == NULL)
    {
        gPrefs = new Preferences();
    }

    return gPrefs;
}

bool Preferences::init()
{
    return true;
}

string Preferences::getEntry(string key)
{
    map<string, string>::iterator iter = fPrefs.find(key);

    if(iter == fPrefs.end())
    {
        return "";
    }
    else
    {
        return iter->second;
    }
}

void Preferences::setEntry(string key, string entry)
{
    fPrefs[key] = entry;
}

vector<string> Preferences::getResourcePaths()
{
    vector<string>	paths;
    char			*resource = getenv("SPACEWARS_RES");

    if(resource)
    {
        paths.push_back(resource);
    }

    return paths;
}

string Preferences::getPrefFileLocation()
{
    return "";
}
