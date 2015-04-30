#ifndef _COBJECT_H
#define _COBJECT_H

#include "cSprite.h"
#include "knightSlash.h"

class cObject : public cSprite
{
private:
	glm::vec2 objectVelocity = glm::vec2(0.0f, 0.0f);

public:
	int playerHealth = 3;
	int score = 0;
	void render();
	void update(float deltaTime);
	void setobjectVelocity(glm::vec2 swordVel);
	glm::vec2 getObjectVelocity();
	void renderCollisionBox();
	bool collidedWith(RECT thisSprite, RECT otherSpritePos);
};

#endif