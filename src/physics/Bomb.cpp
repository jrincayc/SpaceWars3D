
#include "Bomb.h"

Bomb::Bomb(int parent_id, float radius, float termination_time) : 
    Object::Object(false,false)
{
    this->parent_id = parent_id;
    setRadius(radius);
    this->termination_time = termination_time;
    material = new Material();
    material->setAmbient(0.2,0.0,0.0,0.5);
    material->setDiffuse(0.2,0.0,0.0,0.5);
    material->setSpecular(1.0,0.2,0.0,0.5);
    material->setEmission(0.1, 0.00, 0.00, 0.5);
    material->setShininess(5);
    
    innerMaterial = new Material();
    innerMaterial->setAmbient(0.4,0.0,0.0,1.0);
    innerMaterial->setDiffuse(0.6,0.0,0.0,1.0);
    innerMaterial->setSpecular(0.6,0.0,0.0,1.0);
    innerMaterial->setEmission(0.3, 0.00, 0.00, 1.0);
    innerMaterial->setShininess(20);
    
}

void Bomb::draw()
{ 
    glDisable(GL_TEXTURE_2D);
    
    innerMaterial->setGLMaterial();
    drawSphere(fRadius * .1, 25);
    
    glEnable(GL_BLEND);
    material->setGLMaterial();
    drawSphere(fRadius, 25); 
    
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

