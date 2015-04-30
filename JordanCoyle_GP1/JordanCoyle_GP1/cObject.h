#ifndef _COBJECT_H
#define _COBJECT_H

#include "cSprite.h"
#include "knightSlash.h"

class cObject : public cSprite
{
private:
	glm::vec2 objectVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();
	void update(float deltaTime);
	void setobjectVelocity(glm::vec2 swordVel);
	glm::vec2 getObjectVelocity();
};

#endif