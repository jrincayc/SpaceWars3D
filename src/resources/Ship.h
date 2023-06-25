#ifndef __SHIP__
#define __SHIP__

#include "PoweredObject.h"
#include "Resource.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Universe.h"

class Ship;

class ShipObject : public PoweredObject
{
protected:
    Ship	*fShipRes;
    Texture	*fTexture;
    Mesh	*fMesh;
    Material	*fMaterial;
    Universe    *fUniverse;
    Mesh	*fCockpitMesh;
    Texture	*fCockpitTexture;

public:
    ShipObject(Ship *ship);
    virtual ~ShipObject();

    virtual void draw();
    virtual void drawCockpit();
    Ship* getResource() {return fShipRes;}

    void launchBomb();
    void setUniverse(Universe * universe);
};


class Ship : public Resource
{
protected:
    int		fTextureID;
    int		fMeshID;
    float 	fMaxThrust;
    float	fMaxRoll;
    float 	fMaxYaw;
    float	fMaxVertical;
    float	fMaxHorizontal;
    float	fMaxPitch;
    float	fThrustAcc;
    float	fRollAcc;
    float	fYawAcc;
    float	fVerticalAcc;
    float	fHorizontalAcc;
    float 	fPitchAcc;
    Material		*fMaterial;
    float	fRadius;
    float	fMass;
    int		fCockpitMeshID;
    int		fCockpitTextureID;

public:
    Ship();
    virtual ~Ship();

    virtual bool initWithXMLNode(DOMElement *aNode);

    virtual Object* createObject();


    int getTextureID() {return fTextureID;}
    int getMeshID() {return fMeshID;}
    int getCockpitMeshID() {return fCockpitMeshID;}
    int getCockpitTextureID() {return fCockpitTextureID;}
    Material* getMaterial() {return fMaterial;}

    float getThrustAcc() {return fThrustAcc;}
    float getVerticalAcc() {return fVerticalAcc;}
    float getHorizontalAcc() {return fHorizontalAcc;}
    float getPitchAcc() {return fPitchAcc;}
    float getYawAcc() {return fYawAcc;}
    float getRollAcc() {return fRollAcc;}
    float getMaxYaw() {return fMaxYaw;}
    float getMaxRoll() {return fMaxRoll;}
    float getMaxPitch() {return fMaxPitch;}
};



#endif
