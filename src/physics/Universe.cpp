/* -*- C++ -*-
 *  Universe.cpp
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Thu Apr 3 2003.
 *  $Id: Universe.cpp,v 1.14 2003/05/06 18:05:50 jjc Exp $
 */

#include <assert.h>
#include <iostream>
#include <algorithm>
#include "Universe.h"


typedef unsigned int uint;

const float Gc = 1.0;  //Wildly inaccurate gravitational constant.

pair<vector<Vector3D>*,map<int,int>*>
Universe::getCurrentState()
{

    //This will return a list of
    // gravity pairs in the form position,velocity
    // Then in will return following that a list with
    // pairs position, velocity, angular momentum, current direction forward,
    // current direction up
    // and maybe something else.
    vector<Vector3D> * ret_value = new vector<Vector3D>();
    map<int,int> * ret_map = new map<int,int>();
    uint i;
    for(i = 0; i < gravitational_objects.size(); i++)
    {
	//If you change the order here, change the offset and below.
	//If you change the number change the state_stride.
	ret_value->push_back(gravitational_objects[i]->getLocation());
	ret_value->push_back(gravitational_objects[i]->getVelocityVec());
	(*ret_map)[gravitational_objects[i]->getID()] = i;
    }
    uint j = gravitational_objects.size();
    for(i = 0; i < nongravitational_objects.size(); i++)
    {
	//No sense in calculating a dead horse.
	if(nongravitational_objects[i]->isAlive())
	{
	    ret_value->push_back(nongravitational_objects[i]->getLocation());
	    ret_value->push_back(nongravitational_objects[i]->
				 getVelocityVec());
	    (*ret_map)[nongravitational_objects[i]->getID()] = j;
	    j++;
	}
    }
    return pair<vector<Vector3D>*,map<int,int>*>(ret_value,ret_map);
}

void Universe::applyCurrentState(vector<Vector3D> * state,map<int,int>* id_map)
{
    uint i;
    for(i = 0; i < all_objects.size(); i++)
    {
	Object * object = all_objects[i];
	map<int,int>::iterator p = id_map->find(object->getID());
	if(p != id_map->end())
	{
	    //found object
	    int state_index = p->second;
	    uint x = state_index*state_stride;
	    object->setLocation(state->at(x+loc_offset));
	    object->setVelocityVec(state->at(x+vel_offset));
	} else {
	    //Object not found in id_map.
	    //This will happen when the object is new.
	}
    }
}


void Universe::getDerivatives(const vector<Vector3D> * currentState,
			      const float currentTime,
			      vector<Vector3D> * derivatives,
			      map<int,int> * currentMap)
{
    typedef map<int,int>::const_iterator CI;
    for(CI p = currentMap->begin(); p != currentMap->end(); ++p)
    {
	int id = p->first;
	int index = p->second;
	Object * object = getObject(id);

	Vector3D total_acceleration; //= Vector(0,0,0)
	for(uint j = 0; j < gravitational_objects.size(); j++) {
	    total_acceleration +=
		getAcceleration(currentState->at(j*state_stride+loc_offset),
				gravitational_objects.at(j)->getMass(),
				currentState->at(index*state_stride+loc_offset));
	}
	if(object->isPowered()) {
	    total_acceleration +=
	      object->getAcceleration(currentTime);
	}

	//Set the derivative of position equal to the velocity
	derivatives->at(index*state_stride+loc_offset) =
	    currentState->at(index*state_stride+vel_offset);
	derivatives->at(index*state_stride+vel_offset) = total_acceleration;
    }
}

//getDerivatives will return the dp,dv,dL,df,dc vectors for
// all the vectors.

Vector3D Universe::getAcceleration(Vector3D mass_position, float mass,
				   Vector3D object_position) {
    Vector3D difference = mass_position - object_position;
    float mag = difference.mag();
    if(mag < 1.0e-10) {//two posibilities can cause this.
	//1.  the mass and teh object are the same.
	//2.  the mass and the object are about to overflow.
	// in either case, I think we don't want a massive acceleration
	// or maybe even an overflow.
	return 0.0 * difference;
    }

    return (mass / pow(mag,3)) * difference;
}

void getDerivatives(const vector<Vector3D>* currentState,
		    const float currentTime,
		    vector<Vector3D>* derivatives,void * extra)
{
    pair<Universe *,map<int,int> *>* dataPair
	= static_cast< pair<Universe *,map<int,int>*> * >(extra);
    Universe * universe = dataPair->first;
    universe->getDerivatives(currentState,currentTime,derivatives,
			     dataPair->second);
}

void Universe::gotoNextTime(float delta_time)
{
    map<int,int>*  pastID;
    vector<Vector3D>* pastState;
    bool delete_past_state = false;
    if(time_list_valid)
    {
	//Copy these so that they can safely be deleted
	//Idealy would do some kind of reference counting
	pastID = new map<int,int>(*pastIDs.at(lastValidTimeIndex));
	pastState = pastStates.at(lastValidTimeIndex);
    } else {
	//Update all old objects.
	if(lastValidTimeIndex >= 0 && pastStates.at(lastValidTimeIndex) != nullptr)
	{
	    applyCurrentState(pastStates.at(lastValidTimeIndex),
			      pastIDs.at(lastValidTimeIndex));
	}
	pair<vector<Vector3D>*,map<int,int>*> oldState = getCurrentState();
	pastState = oldState.first;
	delete_past_state = true;
	pastID = oldState.second;
    }
    //Does C++ null initial pointers?
    if(pastIDs.at(nextTimeIndex) != nullptr)
    {
	delete pastIDs.at(nextTimeIndex);
	pastIDs.at(nextTimeIndex) = nullptr;
    }
    if(pastStates.at(nextTimeIndex) != nullptr)
    {
	delete pastStates.at(nextTimeIndex);
	pastStates.at(nextTimeIndex) = nullptr;
    }

    //Give the objects a chance to update themselves, however they want.
    for(uint i = 0; i < all_objects.size();i++)
    {
      if(all_objects.at(i)->isAlive()) {
	all_objects.at(i)->updateTime(currentTime,delta_time);
	if(all_objects.at(i)->getIsDead()) {
	    //Objects can decide that it is time to die.
	    time_list_valid = false;
	    has_dead_objects = true;
	}
      }
    }

    //Update the physics model.
    vector<Vector3D> * nextState = new vector<Vector3D>(pastState->size());
    pair<Universe *,map<int,int> *>* dataPair =
	new pair<Universe *,map<int,int> *>(this,pastID);
    rk4vector(pastState, currentTime, delta_time,::getDerivatives,nextState,
	      dataPair);

    delete dataPair;


    currentTime += delta_time;
    pastIDs.at(nextTimeIndex) = pastID;
    pastStates.at(nextTimeIndex) = nextState;
    pastTimesMap.erase(pastTimes[nextTimeIndex]);
    pastTimes.at(nextTimeIndex) = currentTime;
    pastTimesMap[currentTime] = nextTimeIndex;

    if(delete_past_state)
    {   //Need to delete data created with getCurrentState
	delete pastState;
	//Note that the ids will be deleted with the
	//above delete pastIDs[nextTimeIndex]
    }

    time_list_valid = true;
    lastValidTimeIndex = nextTimeIndex;
    nextTimeIndex = (nextTimeIndex + 1) % number_of_past_states;

    //Check for collusions.  We only care about collutions between powered
    //objects and other stuff, not between other stuff and other stuff.
    for(uint i = 0; i < powered_objects.size(); i++)
    {
	int iID = powered_objects.at(i)->getID();
	if(hasObjectInformation(currentTime,iID)) {
	    float iRadius = powered_objects.at(i)->getRadius();
	    Vector3D position = getObjectLocation(currentTime,iID);
	    for(uint j = 0; j < all_objects.size();j++)	{
		int oID = all_objects.at(j)->getID();
		if(oID != iID && hasObjectInformation(currentTime,oID)) {
		    Vector3D other_position =
			getObjectLocation(currentTime,oID);
		    float other_radius = all_objects.at(j)->getRadius();
		    float differenceSquared =
			(other_position-position).magSquared();
		    if(pow(other_radius+iRadius,2) > differenceSquared) {
			powered_objects.at(i)->collide(oID);
			if(powered_objects.at(i)->getIsDead()) {
				cout<< "Object: " << iID
				    << " crashed into "<< oID << endl;
				//Need to recalculate list if the object
				//was killed
				time_list_valid = false;
				has_dead_objects = true;
			    }
		    }
		}
	    }
	}
    }
}

void
Universe::clearDeadObjects()
{
    if(!has_dead_objects)
    {
	return;
    }
    int dead_objects_found = 0;
    int dead_objects_buried = 0;
    vector<Object *> kill_list;
    for(uint i = 0; i < all_objects.size(); i++)
    {
	if(all_objects.at(i)->getIsDead())
	{
	    int id = all_objects.at(i)->getID();
	    dead_objects_found++;
	    bool zombie_object = false;
	    for(uint j = 0; j < pastIDs.size();j++)
	    {
		map<int,int>::iterator p = pastIDs.at(j)->find(id);
		if(p!=pastIDs.at(j)->end())
		{
		    //Still in past list, can't delete yet.
		    zombie_object = true;
		}
	    }
	    if(!zombie_object) {
		//Need to remove from all lists and then delete.
		Object * pointer = all_objects.at(i);
		kill_list.push_back(pointer);
	    }
	}
    }
    for(uint i = 0; i < kill_list.size(); i++)
    {
	Object * pointer = kill_list.at(i);
	int id = pointer->getID();
	map_to_objects.erase(id);
	all_objects.erase(remove(all_objects.begin(),all_objects.end(),
				 pointer),all_objects.end());
	powered_objects.erase(remove(powered_objects.begin(),
				     powered_objects.end(),pointer),
			      powered_objects.end());
	nongravitational_objects.erase(remove(nongravitational_objects.begin(),
					      nongravitational_objects.end(),
					      pointer),
				       nongravitational_objects.end());
	//Note: not checking gravitational objects because they
	// are immortal.
	delete pointer;
	dead_objects_buried++;
    }
    if(dead_objects_buried == dead_objects_found)
    {
	has_dead_objects = false;
    }
}
