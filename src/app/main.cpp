
#include "Canvas.h"
#include "Camera.h"
#include "GLHeaders.h"
#include "Universe.h"
#include "ResourceManager.h"
#include "SolarMap.h"
#include "Resource.h"
#include "PlayerInput.h"
#include "Ship.h"
#include "ShipInput.h"
#include "PlayerInput.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <xercesc/util/PlatformUtils.hpp>

Canvas		*gCanvas;
float		gSpeed;
ShipInput	*gShipInput;
ShipObject	*gShip;

bool		gExit;
bool		gToggleView;

void initSDL(int width, int height, bool fullscreen);
void initOpenGL();
void initManagers();
void setupUniverse(int default_map,int default_ship);
void setupKeys();

const Uint32	kMinTime = 17;

int main(int argc, char *argv[])
{
    Uint32		prevTicks;
    Uint32		newTicks;
    Uint32      	currentSlice = 0;
    Uint32		diffTicks;
    bool		lastViewToggle = false;

    int width = 800;
    int height = 600;
    bool fullscreen = false;
    int default_map = -1;
    int default_ship = -1;
    
    for(int i = 1; i < argc; i++) {
	if (! strcmp(argv[i],"-1")) {
	    width = 640;
	    height = 480;
	} else if(! strcmp(argv[i],"-2")) {
	    width = 800;
	    height = 600;
	} else if(! strcmp(argv[i],"-3")) {
	    width = 1024;
	    height = 768;
	} else if(! strcmp(argv[i],"-m")) {
	    i++;
	    default_map = atoi(argv[i]);
	} else if(! strcmp(argv[i],"-s")) {
	    i++;
	    default_ship = atoi(argv[i]);
	} else if(! strcmp(argv[i],"-f")) {
	    fullscreen = true;
	}
    }
	    
    
    initSDL(width,height,fullscreen);
    initOpenGL();
    initManagers();
    
    setupUniverse(default_map,default_ship);
    setupKeys();

    prevTicks = SDL_GetTicks();
    gSpeed = 0.001;
    while(1)
    {
        if(gExit)
        {
            SDL_Quit();
            exit(0);
        }
        currentSlice++;
        newTicks = SDL_GetTicks();
        diffTicks = newTicks - prevTicks;
        if(diffTicks < kMinTime)
        {
            SDL_Delay(kMinTime - diffTicks);
	    newTicks = SDL_GetTicks();
	    diffTicks = newTicks - prevTicks;
        }
        PlayerInput::getSharedInput()->processEvents(gSpeed * diffTicks * .0625, diffTicks / 1000.0);
        gShipInput->update();
        gCanvas->getUniverse()->gotoNextTime(gSpeed * diffTicks * .0625);
        if(currentSlice % 100 == 0)
        {
            gCanvas->getUniverse()->clearDeadObjects();
        }
        if(gToggleView != lastViewToggle)
        {
            lastViewToggle = gToggleView;
            gCanvas->getCamera()->setChaseObjectID(gShip->getID());
            gCanvas->getCamera()->setMode(gCanvas->getCamera()->getMode() + 1);
        }
        gCanvas->draw();
        prevTicks = newTicks;
    }
}

void initSDL(int width, int height, bool fullscreen)
{
    const SDL_VideoInfo* info = NULL;
    int extra_flags = 0;
    if(fullscreen) 
    {
	extra_flags |= SDL_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Failed to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    SDL_EnableUNICODE(1);

    info = SDL_GetVideoInfo( );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(SDL_SetVideoMode(width, height, 32, SDL_OPENGL | extra_flags) == 0)
    {
        cerr << "Failed to set up the prefered SDL video mode: " 
	     << SDL_GetError() << endl;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if(SDL_SetVideoMode(width, height, 16, SDL_OPENGL | extra_flags) == 0) 
	{ 
	    cerr << "Failed to set up fallback SDL video mode: " 
		 << SDL_GetError() << endl;

	    exit(1);
	}
    }
}

void initOpenGL()
{
    glShadeModel( GL_SMOOTH );

    // Culling
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    // Set the clear color
    glClearColor( 0, 0, 0, 0 );

    // Textures
    glEnable(GL_TEXTURE_2D);

    // lights are fun
    glEnable(GL_LIGHTING);

    // turn on vertex arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
}

void initManagers()
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
            << message << "\n";
        XMLString::release(&message);
        exit(1);
    }


    ResourceManager::getSharedManager()->init();

    cout << *ResourceManager::getSharedManager();
}

void setupUniverse(int default_map, int default_ship)
{
    Universe 			*universe = new Universe();
    ResourceManager		*resManager = ResourceManager::getSharedManager();
    vector<Resource*>	*resList = resManager->getResourcesOfType(kSolarMapType);
    SolarMap			*map;
    unsigned int		index;
    ShipObject			*ship;

    if(resList->size() == 0)
    {
        cerr << "Hmm... we have no solar maps to load." << endl;
        exit(0);
    }
    else if(resList->size() == 1)
    {
        map = (SolarMap*)(*resList)[0];
    }
    else if(default_map >= 0 && (uint)default_map < resList->size()) 
    {
	map = (SolarMap*)resList->at(default_map);
    }
    else
    {
        cout << "Select Map:" << endl;
        for(unsigned int i = 0; i < resList->size(); i++)
        {
            cout << "\t" << i << ")" << (*resList)[i]->getName() << endl;
        }
        cout << "Enter Selection: ";
        cin >> index;
        if(index >= resList->size() || index < 0)
        {
            cerr << "Invalid Input" << endl;
            exit(1);
        }
        map = (SolarMap*)(*resList)[index];
    }

    map->populateUniverse(universe);

    // lets put the ship in
    resList = resManager->getResourcesOfType(kShipType);
    if(resList->size() == 0)
    {
        cerr << "Sorry, we have no ships for you to fly." << endl;
        exit(0);
    }
    else if(resList->size() == 1)
    {
        ship = (ShipObject*)(*resList)[0]->createObject();
    }
    else if(default_ship >= 0 && (uint)default_ship < resList->size()) 
    {
	ship = (ShipObject*)resList->at(default_ship)->createObject();
    }
    else
    {
        cout << "Select your ship:" << endl;
        for(unsigned int i = 0; i < resList->size(); i++)
        {
            cout << "\t" << i << ")" << (*resList)[i]->getName() << endl;
        }
        cout << "Enter Selection: ";
        cin >> index;
        if(index >= resList->size() || index < 0)
        {
            cerr << "Invalid Input" << endl;
            exit(1);
        }
        ship = (ShipObject*)(*resList)[index]->createObject();
    }

    ship->setLocation(Vector3D(-3000, 0, 0));
    ship->setUniverse(universe);
    universe->addPoweredObject(ship);
    gShip = ship;

    gShipInput = new ShipInput();
    gShipInput->setShip(ship);
    
    gSpeed = 0.05;
    
    gCanvas = new Canvas();
    gCanvas->getCamera()->setShape(40, 640.0/480.0);
    gCanvas->getCamera()->setNear(1);
    gCanvas->getCamera()->setFar(9999999999);
    gCanvas->getCamera()->set(Point3D(3005, 0, 0), Vector3D(1,0,0), Vector3D(0,0,1));
    gCanvas->setUniverse(universe);
}

void setupKeys()
{
    PlayerInput	*input = PlayerInput::getSharedInput();

    gExit = false;
    gToggleView = false;

    input->addInput(new KeyInput(SDLK_ESCAPE, new ToggleInput(&gExit)));
    input->addInput(new KeyInput('`', new ToggleInput(&gToggleView)));
    input->addInput(new KeyInput('-', new StepInput(&gSpeed, -1, 1, -.001, true, true)));
    input->addInput(new KeyInput('=', new StepInput(&gSpeed, -1, 1, .001, true, true)));
}
