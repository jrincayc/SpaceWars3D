#ifndef __PLAYERINPUT__
#define __PLAYERINPUT__

#include <map>
#include <SDL/SDL.h>

using namespace std;

class Input
{
protected:
    bool	fUseRealTime;
    
public:
    Input(bool useRealTime = false);
    virtual ~Input() {;}

    virtual void keyDown(SDL_Event *event) {;}
    virtual void keyUp(SDL_Event *event) {;}

    void doUpdate(float timeDelta, float realTimeDelta);
    virtual void update(float timeDelta) {;}
};


class ToggleInput : public Input
{
protected:
    bool	*fToggle;

public:
    ToggleInput(bool *toggle);

    virtual void keyDown(SDL_Event *event);
};

class PushInput : public Input
{
protected:
    bool	*fPush;
    bool	fOurPush;

public:
    PushInput(bool *push, bool realTime = false);
    virtual ~PushInput();

    virtual void keyDown(SDL_Event *event);
    virtual void keyUp(SDL_Event *event);
};

class StepInput : public PushInput
{
protected:
    float	*fStorage;
    float	fMin;
    float	fMax;
    float	fStep;
    bool	fContinuous;
    bool	fWrap;

public:
    StepInput(float *storage, float min, float max, float step, bool continuous = true, bool realTime = false);

    virtual void keyDown(SDL_Event *event);

    virtual void update(float timeDelta);

protected:
    void add(float amount);
};

class AcceleratedInput : public StepInput
{
protected:
    float	fVelocity;
    float	fMaxVelocity;
    float	fMinVelocity;
    float	fNetural;
    
public:
    AcceleratedInput(float *storage, float min, float max, float netural, float acc, float maxVelocity, float minVelocity, bool realTime = false);

    virtual void keyDown(SDL_Event *event);
    virtual void keyUp(SDL_Event *event);
    virtual void update(float timeDelta);
};


class KeyInput
{
protected:
    Input	*fInput;
    int		fKey;

public:
    KeyInput(int key, Input *input);
    virtual ~KeyInput();

    int getKey() {return fKey;}
    void setKey(int key) {fKey = key;}

    virtual void keyDown(SDL_Event *event);
    virtual void keyUp(SDL_Event *event);

    virtual void update(float timeDelta, float realTimeDelta);
};

class PlayerInput
{
protected:
    map<int, KeyInput*>	fKeyEntries;

public:
    PlayerInput();
    virtual ~PlayerInput();

    static PlayerInput* getSharedInput();

    void addInput(KeyInput *input);

    void processEvents(float timeDelta, float realTimeDelta);

protected:
    void handleKeyDown(SDL_Event *event);
    void handleKeyUp(SDL_Event *event);
};






#endif
