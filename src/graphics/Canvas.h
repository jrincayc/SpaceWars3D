/*  -*- C++ -*-
 *  Canvas.h
 *  SpaceWars3D
 *
 *  $Id: Canvas.h,v 1.9 2003/05/09 21:01:33 milvich Exp $
 */



#ifndef __CANVAS__
#define __CANVAS__

#include <map>
#include "GLHeaders.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Camera.h"
#include "Universe.h"
#include "StarField.h"
#include "PlayerInput.h"


class Canvas
{
protected:
    Camera			*fCamera;
    Universe		*fUniverse;
    map<int,Object *>    fObjects;
    bool                 fClientMode;
    StarField		 *fStarField;
    void drawObject(Object * object,Vector3D location, Vector3D velocity);
    vector<Object*> * getObjects();
    bool		 fShowVectors;

public:
    Canvas(bool client_mode = false);
    ~Canvas();

    void reshape(int width, int height);
    void draw();

    void setUniverse(Universe *universe);
    Universe* getUniverse() {
	assert(not fClientMode);
	return fUniverse;}
    void addObject(Object * object);
    void removeObject(Object * object);
    Object * getObject(int id);
    bool hasObject(int id);
    Vector3D getObjectLocation(int id);
    Vector3D getObjectVelocity(int id);

    Camera* getCamera() {return fCamera;}
protected:
    void init();
    void setupControls();
};



#endif
