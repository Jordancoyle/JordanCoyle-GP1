#include "cKnight.h"

void cKnight::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID);

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void cKnight::update(float deltaTime)
{
	setBoundingRect(&boundingRect);

	for (vector<cObject*>::iterator objectIterartor = theObjects.begin(); objectIterartor != theObjects.end(); ++objectIterartor)
	{
		(*objectIterartor)->update(deltaTime);
		//for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		//{
		if (this->collidedWith(this->getBoundingRect(), (*objectIterartor)->getBoundingRect()))
		{
			// if a collision set the bullet and asteroid to false
			//(*asteroidIterator)->setActive(false);
			(*objectIterartor)->setActive(false);
			playerHealth--;
		}
		//}
	}
}

void cKnight::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	//glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), -(textureHeight / 2));
	//glVertex2f((textureWidth / 2), (textureHeight / 2));
	//glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));

	glEnd();

	glPopMatrix();
}

void cKnight::setPlayerHealth(int health = 3)
{
	playerHealth = health;
}

int cKnight::getPlayerHealth()
{
	return playerHealth;
}