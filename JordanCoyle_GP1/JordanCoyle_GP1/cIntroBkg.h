#ifndef _CINTROBKG_H
#define _CINTROBKG_H
#include "cSprite.h"

class cIntroBkg : public cSprite
{
public:
	void render();
	void update(float deltaTime);
};
#endif