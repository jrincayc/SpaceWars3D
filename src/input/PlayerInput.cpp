#include "PlayerInput.h"
#include <iostream>

Input::Input(bool useRealTime)
{
    fUseRealTime = useRealTime;
}

void Input::doUpdate(float timeDelta, float realTimeDelta)
{
    if(fUseRealTime)
    {
        update(realTimeDelta);
    }
    else
    {
        update(timeDelta);
    }
}


ToggleInput::ToggleInput(bool *toggle)
    : Input(true)
{
    fToggle = toggle;
}

void ToggleInput::ToggleInput::keyDown(SDL_Event *event)
{
    *fToggle = !*fToggle;
}


PushInput::PushInput(bool *push, bool realTime)
    : Input(realTime)
{
    if(push == NULL)
    {
        fPush = new bool;
        *fPush = false;
        fOurPush = true;
    }
    else
    {
        fPush = push;
        fOurPush = false;
    }
}

PushInput::~PushInput()
{
    if(fOurPush)
    {
        delete fPush;
        fPush = NULL;
    }
}

void PushInput::keyDown(SDL_Event *event)
{
    *fPush = true;
}

void PushInput::keyUp(SDL_Event *event)
{
    *fPush = false;
}


StepInput::StepInput(float *storage, float min, float max, float step, bool continuous, bool realTime)
    : PushInput(NULL, realTime)
{
    fStorage = storage;
    fMin = min;
    fMax = max;
    fStep = step;
    fContinuous = continuous;
}

void StepInput::keyDown(SDL_Event *event)
{
    PushInput::keyDown(event);
    if(!fContinuous)
    {
        add(fStep);
    }
}

void StepInput::update(float timeDelta)
{
    if(fContinuous && *fPush)
    {
        add(fStep * timeDelta);
    }
}

void StepInput::add(float amount)
{
    *fStorage += fStep;
    if(*fStorage < fMin)
    {
        *fStorage = fMin;
    }
    else if(*fStorage > fMax)
    {
        *fStorage = fMax;
    }
}

AcceleratedInput::AcceleratedInput(float *storage, float min, float max, float netural, float acc, float maxVelocity, float minVelocity, bool realTime)
    : StepInput(storage, min, max, acc, true, realTime)
{
    fVelocity = 0;
    fMaxVelocity = maxVelocity;
    fMinVelocity = minVelocity;
    fNetural = netural;
}

void AcceleratedInput::keyDown(SDL_Event *event)
{
    StepInput::keyDown(event);
    fVelocity = 0;
}

void AcceleratedInput::keyUp(SDL_Event *event)
{
    StepInput::keyUp(event);
    fVelocity = 0;
    *fStorage = fNetural;
}

void AcceleratedInput::update(float timeDelta)
{
    if(*fPush)
    {
        fVelocity += fStep * timeDelta;
        if(fVelocity > fMaxVelocity)
        {
            fVelocity = fMaxVelocity;
        }
        else if(fVelocity < fMinVelocity)
        {
            fVelocity = fMinVelocity;
        }

        add(fVelocity);
    }
}


KeyInput::KeyInput(int key, Input *input)
{
    fKey = key;
    fInput = input;
}

KeyInput::~KeyInput()
{
    delete fInput;
}

void KeyInput::keyDown(SDL_Event *event)
{
    fInput->keyDown(event);
}

void KeyInput::keyUp(SDL_Event *event)
{
    fInput->keyUp(event);
}

void KeyInput::update(float timeDelta, float realTimeDelta)
{
    fInput->doUpdate(timeDelta, realTimeDelta);
}

PlayerInput* PlayerInput::getSharedInput()
{
    static PlayerInput	*input = NULL;

    if(input == NULL)
    {
        input = new PlayerInput();
    }
    
    return input;
}

PlayerInput::PlayerInput()
{
    
}

PlayerInput::~PlayerInput()
{
    
}

void PlayerInput::addInput(KeyInput *input)
{
    fKeyEntries[input->getKey()] = input;
}

void PlayerInput::processEvents(float timeDelta, float realTimeDelta)
{
    SDL_Event						event;
    map<int, KeyInput*>::iterator	iter = fKeyEntries.begin();

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                handleKeyDown(&event);
                break;
            case SDL_KEYUP:
                handleKeyUp(&event);
                break;
            case SDL_QUIT:
                SDL_Quit();
                exit(0);
                break;
        }
    }

    while(iter != fKeyEntries.end())
    {
        iter->second->update(timeDelta, realTimeDelta);
        ++iter;
    }
}

void PlayerInput::handleKeyDown(SDL_Event *event)
{
    map<int, KeyInput*>::iterator	iter = fKeyEntries.find(event->key.keysym.sym);

    if(iter != fKeyEntries.end())
    {
        iter->second->keyDown(event);
    }
}

void PlayerInput::handleKeyUp(SDL_Event *event)
{
    map<int, KeyInput*>::iterator	iter = fKeyEntries.find(event->key.keysym.sym);

    if(iter != fKeyEntries.end())
    {
        iter->second->keyUp(event);
    }
}
