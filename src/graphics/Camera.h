#include "Point3D.h"
#include "Vector3D.h"
#include "Affine.h"
#include "PlayerInput.h"
#include "Object.h"
#include "Quaternion.h"
#include "Canvas.h"

#ifndef __CAMERA__
#define __CAMERA__

const float	kDefaultSlideDist = 2.0;
const float	kDefaultDegrees = 3.0;

class Canvas;

class Camera
{
protected:
    Vector3D	fLocVec;
    Vector3D	fU, fV, fN;
    Affine3D	fModelMatrix;
    float	fViewAngle, fAspectRatio, fNear, fFar;
    Canvas      *fCanvas;

    float	fRollInput, fPitchInput, fYawInput, fVertSlideInput, fHorzSlideInput, fForwardInput;

    int		fMode;
    int		fChaseObjectID;
    float	fChaseDistance;
    Quaternion	fChaseQ;

public:
    Camera();

    enum {kGlobal, kChase, kTrail, kCockpit};

    void set(const Point3D &location, const Vector3D &direction, const Vector3D &up);
    void roll(const float &angle);
    void pitch(const float &angle);
    void yaw(const float &angle);
    void slide(const Vector3D &vec);

    Point3D getLocation() const { return fLocVec;}

    void setShape(const float &vAngle, const float &aspectRatio);
    void setNear(const float &near);
    void setFar(const float &far);

    void updateGLCamera();
    void setCanvas(Canvas *canvas) {fCanvas = canvas;}

    void setChaseObjectID(int id);
    int getChaseObjectID() {return fChaseObjectID;}
    void setMode(int mode);
    int getMode() {return fMode;}

protected:
    void setUpMatrix();
    void setUpControls();
    void readControls();
    void readControlsChase();
    void readControlsGlobal();
    void readControlsTrail();
    void readControlsCockpit();
};

#endif
