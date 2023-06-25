#include "LightManager.h"
#include <iostream>

LightManager::LightManager()
{
    for(int i = 0; i < kMaxLights; i++)
    {
        fLights[i] = NULL;
    }
}

LightManager::~LightManager()
{
    
}

LightManager* gLightManager = NULL;
LightManager* LightManager::getLightManager()
{
    if(gLightManager == NULL)
    {
        gLightManager = new LightManager();
    }

    return gLightManager;
}

void LightManager::updateLights()
{
    for(int i = 0; i < kMaxLights; i++)
    {
        if(fLights[i] != NULL)
        {
            fLights[i]->doGLLightStuff();
        }
    }
}

void LightManager::addLight(Light *light)
{
    // first make sure it isn't already added
    for(int i = 0; i < kMaxLights; i++)
    {
        if(fLights[i] == light)
        {
            return;
        }
    }

    for(int i = 0; i < kMaxLights; i++)
    {
        if(fLights[i] == NULL)
        {
            fLights[i] = light;
            switch(i)
            {
                case 0:
                    light->setLightID(GL_LIGHT0);
                    break;
                case 1:
                    light->setLightID(GL_LIGHT1);
                    break;
                case 2:
                    light->setLightID(GL_LIGHT2);
                    break;
                case 3:
                    light->setLightID(GL_LIGHT3);
                    break;
                case 4:
                    light->setLightID(GL_LIGHT4);
                    break;
                case 5:
                    light->setLightID(GL_LIGHT5);
                    break;
                case 6:
                    light->setLightID(GL_LIGHT6);
                    break;
                case 7:
                    light->setLightID(GL_LIGHT7);
                    break;
            }
            light->enable();
            return;
        }
    }
}

void LightManager::removeLight(Light * light)
{
    for(int i = 0; i < kMaxLights; i++)
    {
        if(fLights[i] == light)
        {
            fLights[i] = NULL;
            light->disable();
        }
    }
}
