#ifndef _CSWORD_H
#define _CSWORD_H

#include "cSprite.h"
#include "knightSlash.h"

class cSword : public cSprite
{
private: 
	glm::vec2 swordVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();
	void update(float deltaTime);
	void setswordVelocity(glm::vec2 swordVel);
	glm::vec2 getSwordVelocity();
	void renderCollisionBox();
};

#endif