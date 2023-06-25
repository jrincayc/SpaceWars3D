

#ifndef __PREFS__
#define __PREFS__

#include <map>
#include <string>
#include <vector>

using namespace std;

class Preferences
{
protected:
    map<string, string>	fPrefs;

public:
    Preferences();
    ~Preferences();

    static Preferences* getSharedPreferences();

    bool init();
    bool savePrefs();

    string getEntry(string key);
    void setEntry(string key, string entry);

    vector<string> getResourcePaths();

protected:
    string getPrefFileLocation();
};




#endif
