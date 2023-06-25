
#ifndef __STARFIELDS__
#define __STARFIELDS__

#include "GLHeaders.h"

class StarField
{
protected:
    GLfloat	*fStarPoints;
    int		fNumStars;
    
public:
    StarField(float distance, int numStars);
    ~StarField();
    
    void draw();
};


#endif

