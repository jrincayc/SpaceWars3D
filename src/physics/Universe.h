/* -*- C++ -*-
 *  Universe.h
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati on Thu Apr 3 2003.
 *  $Id: Universe.h,v 1.12 2003/05/07 20:05:13 jjc Exp $
 */

#ifndef __Universe__
#define __Universe__

#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include "Object.h"
#include "Vector3D.h"
#include "ODE.h"
#include "assert.h"

const int null = 0;

class Universe
{
protected:
    //Objects that have a calculated  gravitational effect.
    vector<Object *> gravitational_objects; 

    //List of all objects currently tracked by the physics model
    vector<Object *> all_objects;

    //Map from object ids to objects
    map<int,Object *>     map_to_objects;

    //List of all objects that have thrusters
    vector<Object *> powered_objects;

    //List of all objects that are not gravitational_objects
    vector<Object *> nongravitational_objects;

    static const int number_of_past_states = 10;

    //List of past time slices
    vector<vector<Vector3D> *>  pastStates;

    //Map from object ids to their index in pastStates
    vector<map<int,int>*>       pastIDs;

    //time at a give index
    vector<float>              pastTimes; 

    //Map from time to index
    map<float,int>             pastTimesMap;

    int nextTimeIndex;
    int lastValidTimeIndex;

    bool time_list_valid; 
    bool has_dead_objects;

    float currentTime;

    Vector3D getAcceleration(Vector3D mass_position, float mass,
			     Vector3D object_position);

    void addStandardObject(Object * object) {
	all_objects.push_back(object);
	time_list_valid = false;
	map_to_objects[object->getID()] = object;
    }

    /*!
      @function getCurrentState
      @abstract returns a vector of the currentState.
      @result Returns a vector that describes the current state. 
       and a map from object ids to object indexs in the vector.
     */
    pair<vector<Vector3D>*,map<int,int>*> getCurrentState();

    void applyCurrentState(vector<Vector3D>* state,map<int,int>* id_map);

    void getDerivatives(const vector<Vector3D> * currentState, 
			float currentTime, vector<Vector3D> * derivatives,
			map<int,int> * currentMap);
    
    friend void getDerivatives(const vector<Vector3D>* currentState,
			       const float currentTime,
			       vector<Vector3D>* derivatives,void * extra);

    //Layout of state vectors
    static const int state_stride = 2;
    static const int loc_offset = 0;
    static const int vel_offset = 1;

    int getObjectIndex(float time, int id) {
        uint time_index = pastTimesMap[time];
	assert(0 <= time_index && time_index < pastTimes.size());
	assert(pastIDs[time_index]->find(id) != pastIDs[time_index]->end());
	int object_index = pastIDs[time_index]->find(id)->second;
	int x = object_index*state_stride;
	return x;
    }

public:
    Universe() {
	time_list_valid = false;
	has_dead_objects = false;
	currentTime = 0.0;
	nextTimeIndex = 0;
	lastValidTimeIndex = -1;
	pastStates.resize(number_of_past_states);
	for(uint i = 0; i < pastStates.size(); i++) {
	  pastStates[i] = null;
	}	 
	pastIDs.resize(number_of_past_states);
	pastTimes.resize(number_of_past_states);
    }

    void addGravitationalObject(Object * object) {
	gravitational_objects.push_back(object);
	addStandardObject(object);
    object->addedToUniverse();
    }

    void addPoweredObject(Object * object) {
	powered_objects.push_back(object);
	nongravitational_objects.push_back(object);
	addStandardObject(object);
    }

    void addNonPoweredObject(Object * object) {
	nongravitational_objects.push_back(object);
	addStandardObject(object);
    }

    //Don't ever pass any function a time not gotten from 
    // this class, unless you trust floating compare more than 
    // I do.
    float getLastValidTime() {
	return pastTimes[lastValidTimeIndex];
    }

    bool hasObjectInformation(float time, int id) {
	if(pastTimesMap.find(time) == pastTimesMap.end()) {
	    return false;
	}
        uint time_index = pastTimesMap[time];
	if(pastIDs[time_index]->find(id) != pastIDs[time_index]->end()) {
	    return true;
	} else {
	    return false;
	}
    }

    Vector3D getObjectLocation(float time,int id) {
	int time_index = pastTimesMap[time];
	int x  = getObjectIndex(time,id) + loc_offset;
	return (*(pastStates[time_index]))[x];
    }

    Vector3D getObjectVelocity(float time,int id) {
	int time_index = pastTimesMap[time];
	int x  = getObjectIndex(time,id) + vel_offset;
	return (*(pastStates[time_index]))[x];
    }

    Object * getObject(int id) {
	return map_to_objects[id];
    }

    bool hasObject(int id) {
	if(map_to_objects.find(id) == map_to_objects.end()) {
	    return false;
	} else {
	    return true;
	}
    }
    
    void gotoNextTime(float delta_time);
    void clearDeadObjects();

    const vector<Object*> getObjects() {return all_objects;}
};

#endif //ifndef __Universe__
