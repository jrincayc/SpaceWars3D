#include "StarField.h"
#include "Vector3D.h"
#include "Utility.h"
#include "Material.h"
#include <stdlib.h>

StarField::StarField(float distance, int numStars)
{
    Vector3D	temp;
    
    fStarPoints = new GLfloat[numStars * 3];
    fNumStars = numStars;
    
    for(int i = 0; i < numStars; i++)
    {
        temp[0] = randomFloat() - .5;
	temp[1] = randomFloat() - .5;
	temp[2] = randomFloat() - .5;
	
	temp = temp.makeSize(distance);
	
	fStarPoints[i * 3 + 0] = temp[0];
	fStarPoints[i * 3 + 1] = temp[1];
	fStarPoints[i * 3 + 2] = temp[2];
    }
}

StarField::~StarField()
{
    delete [] fStarPoints;
}
    
void StarField::draw()
{
    Material	mat;
    
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glColor3f(1.0, 1.0, 1.0);
    mat.setAmbient(1.0, 1.0, 1.0, 1.0);
    mat.setDiffuse(1.0, 1.0, 1.0, 1.0);
    mat.setSpecular(1.0, 1.0, 1.0, 1.0);
    mat.setEmission(1.0, 1.0, 1.0, 1.0);
    mat.setGLMaterial();
    
    glPointSize(1);
    glVertexPointer(3, GL_FLOAT, 0, fStarPoints);
    glDrawArrays(GL_POINTS, 0, fNumStars);
    
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
