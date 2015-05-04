#ifndef _CKNIGHT_H
#define _CKNIGHT_H

#include "cSprite.h"
#include "knightSlash.h"

class cKnight : public cSprite
{
private:

public:
	int playerHealth = 3;
	void render();
	void update(float deltaTime);
	void renderCollisionBox();
	void setPlayerHealth(int health);
	int getPlayerHealth();
};

#endif