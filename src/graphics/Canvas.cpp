#ifdef __APPLE__
    #include <SDL.h>
#else
    #include <SDL/SDL.h>
#endif
#include "Canvas.h"
#include "GLHeaders.h"
#include "Object.h"
#include "LightManager.h"
#include "Material.h"
#include "PoweredObject.h"
#include "Quaternion.h"
#include "Ship.h"
#include "PlayerInput.h"
#include <iostream>

Canvas::Canvas(bool client_mode)
{
    fClientMode = client_mode;
    init();
    fStarField = new StarField(30000, 3000);
    fShowVectors = false;
}

Canvas::~Canvas()
{
    delete fCamera;
    delete fStarField;
}

void Canvas::reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    fCamera->setShape(60, (float)width / (float)height);
}

vector<Object*> * Canvas::getObjects() {
    if(fClientMode) {
	vector<Object*> * ret_val = new vector<Object*>();
	map<int,Object*>::const_iterator p = fObjects.begin();
	for(;p!=fObjects.end();++p) {
	    ret_val->push_back(p->second);
	}
	return ret_val;
    } else {
	return new vector<Object*>(fUniverse->getObjects());
    }

}

void Canvas::drawObject(Object * object,Vector3D location, Vector3D velocity)
{    
    Material				mat;

    Vector3D				forward = 
	object->getForwardOrientation();
    Vector3D				up =
	object->getUpwardOrientation();

    float length = object->getRadius() * 2;
    glPushMatrix();
    
    glTranslatef(location[0], location[1], location[2]);
    
    if(fShowVectors)
    {
	    glDisable(GL_TEXTURE_2D);
	    
	    glColor3f(1.0, 0.0, 0.0);
	    mat.setAmbient(1.0, 0.0, 0.0, 1.0);
	    mat.setDiffuse(1.0, 0.0, 0.0, 1.0);
	    mat.setSpecular(1.0, 0.0, 0.0, 1.0);
	    mat.setEmission(1.0, 0.0, 0.0, 1.0);
	    mat.setGLMaterial();
	    glBegin(GL_LINES);
	    glVertex3f(0.0,0.0,0.0);
	    (velocity * 2).glVertex();
	    glEnd();
	    
	    glColor3f(0.0, 1.0, 0.0);
	    mat.setAmbient(0.0, 1.0, 0.0, 1.0);
	    mat.setDiffuse(0.0, 1.0, 0.0, 1.0);
	    mat.setSpecular(0.0, 1.0, 0.0, 1.0);
	    mat.setEmission(0.0, 1.0, 0.0, 1.0);
	    mat.setGLMaterial();
	    glBegin(GL_LINES);
	    glVertex3f(0.0,0.0,0.0);
	    forward.makeSize(length).glVertex();
	    glEnd();
	    
	    glColor3f(0.0, 0.0, 1.0);
	    mat.setAmbient(0.0, 0.0, 1.0, 1.0);
	    mat.setDiffuse(0.0, 0.0, 1.0, 1.0);
	    mat.setSpecular(0.0, 0.0, 1.0, 1.0);
	    mat.setEmission(0.0, 0.0, 1.0, 1.0);
	    mat.setGLMaterial();
	    glBegin(GL_LINES);
	    glVertex3f(0.0,0.0,0.0);
	    up.makeSize(length).glVertex();
	    glEnd();
    }

    // setup the view transform
    glMultMatrixf(object->getRotation().getConjugate().getGLMatrix());
    
    glEnable(GL_TEXTURE_2D);
    
    object->draw();
    
    glPopMatrix();
    
}

void Canvas::draw()
{
    const vector<Object*> *	objects = getObjects();
    Vector3D				loc;
    Vector3D                            vel;
    ShipObject			*ship;
    Material				mat;

    for(unsigned int i = 0; i < objects->size(); i++)
    {
        objects->at(i)->prepareToDraw();
    }
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    fCamera->updateGLCamera();
    LightManager::getLightManager()->updateLights();
    
    fStarField->draw();

    for(unsigned int i = 0; i < objects->size(); i++)
    {
        int id = objects->at(i)->getID();
        if(objects->at(i)->getIsDead()){
            //Object dead, don't need to draw.
            continue;
        }
        loc = getObjectLocation(id);
	vel = getObjectVelocity(id);
	drawObject(objects->at(i),loc,vel);
    }
    
    if(hasObject(fCamera->getChaseObjectID()))
    {
	glPushMatrix();
	
        ship = (ShipObject*)getObject(fCamera->getChaseObjectID());
        loc = getObjectLocation(fCamera->getChaseObjectID());
        glTranslatef(loc[0], loc[1], loc[2]);
	
	vel = getObjectVelocity(fCamera->getChaseObjectID());
	
	    glDisable(GL_TEXTURE_2D);
	    
	    glColor3f(1.0, 0.0, 0.0);
	    mat.setAmbient(1.0, 0.0, 0.0, 1.0);
	    mat.setDiffuse(1.0, 0.0, 0.0, 1.0);
	    mat.setSpecular(1.0, 0.0, 0.0, 1.0);
	    mat.setEmission(1.0, 0.0, 0.0, 1.0);
	    mat.setGLMaterial();
	    glBegin(GL_LINES);
	    glVertex3f(0.0,0.0,0.0);
	    (vel * 2).glVertex();
	    glEnd();
	    
	    glEnable(GL_TEXTURE_2D);
	    
	    glPopMatrix();
    }
    
    
    if(fCamera->getMode() == Camera::kCockpit)
    {
        glPushMatrix();
	
        ship = (ShipObject*)getObject(fCamera->getChaseObjectID());
        loc = getObjectLocation(fCamera->getChaseObjectID());
        glTranslatef(loc[0], loc[1], loc[2]);
        glMultMatrixf(ship->getRotation().getConjugate().getGLMatrix());
	glTranslatef(0,2,0);
	ship->drawCockpit();
	
	glPopMatrix();
    }

    glFlush();
    SDL_GL_SwapBuffers();
    delete objects;
}

void Canvas::setUniverse(Universe *universe)
{
    assert(not fClientMode);
    fUniverse = universe;
}

void Canvas::init()
{
    fCamera = new Camera();
    fCamera->setCanvas(this);
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT, GL_SMOOTH);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
    
    setupControls();
}

void Canvas::setupControls()
{
    PlayerInput	*input = PlayerInput::getSharedInput();
    
    input->addInput(new KeyInput('\\', new ToggleInput(&fShowVectors)));

}

void Canvas::addObject(Object * object) {
    assert(fClientMode);
    fObjects[object->getID()] = object;
}

void Canvas::removeObject(Object * object) {
    assert(fClientMode);
    fObjects.erase(object->getID());
}

Object * Canvas::getObject(int id) {
    if(fClientMode) {
	return fObjects[id];
    } else {
	return fUniverse->getObject(id);
    }
}

bool Canvas::hasObject(int id) {
    if(fClientMode) {
	if(fObjects.find(id) == fObjects.end()) {
	    return false;
	} else {
	    return true;
	}
    } else { 
	return fUniverse->hasObject(id) and 
	    fUniverse->getObject(id)->isAlive();
    }
}

Vector3D Canvas::getObjectLocation(int id) {
    if(fClientMode) {
	return getObject(id)->getLocation();
    } else {
	return fUniverse->getObjectLocation(fUniverse->getLastValidTime(),id);
    }
}

Vector3D Canvas::getObjectVelocity(int id) {
    if(fClientMode) {
	return getObject(id)->getVelocityVec();
    } else {
	return fUniverse->getObjectVelocity(fUniverse->getLastValidTime(),id);
    }
}

