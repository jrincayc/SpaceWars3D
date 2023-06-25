/*  -*- C++ -*-
 *  Bomb.h
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Tue May 6 2003.
 *  $Id: Bomb.h,v 1.2 2003/05/09 21:29:43 milvich Exp $
 */

#ifndef __Bomb__
#define __Bomb__


#include "Object.h"
#include "Utility.h"
#include "Material.h"


class Bomb : public Object
{
protected:
    int parent_id;
    float activition_time;
    float termination_time;
    Material *material;
    Material *innerMaterial;

public:

    Bomb(int parent_id, float radius, float termination_time);

    virtual void updateTime(float currentTime, float deltaTime) 
    {
	if(currentTime >= termination_time) {
	    setIsDead(true);
	}
    }

    virtual void draw();
};



#endif //ifndef __Bomb__
