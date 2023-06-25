#ifndef __LIGHTMANAGER__
#define __LIGHTMANAGER__

#include "Light.h"

class LightManager
{
protected:
    // Open gl only allows 8 lights
    static const int kMaxLights = 8;

    Light*	fLights[kMaxLights];

public:
    LightManager();
    virtual ~LightManager();

    static LightManager* getLightManager();

    void updateLights();
    void addLight(Light *light);
    void removeLight(Light * light);
};


#endif
