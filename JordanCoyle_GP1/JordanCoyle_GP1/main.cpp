
#include "cWNDManager.h"
#include "windowOGL.h"
#include "GameConstants.h"
#include "knightSlash.h"
#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevHInstance, LPSTR cmdLine, int cmdShow)
{
	const int screenWidth = 1280,
		screenHeight = 720,
		windowBPP = 16;

	cTexture introTex,
		backGroundTex,
		charTex,
		swordTex,
		tempObjectTex;

	cBkGround backGroundSprite,
		introSprite,
		charSprite;

	cSword swordSprite;

	cObject objectSprite1;

	windowOGL oglWindow;

	static cWNDManager* windowMng = cWNDManager::getInstance();
	static cSoundMgr* soundMng = cSoundMgr::getInstance();
	static cInputMgr* inputMng = cInputMgr::getInstance();

	windowMng->attachOGLWnd(&oglWindow);
	windowMng->attachInputMgr(inputMng);

	if (!windowMng->createWND(screenWidth, screenHeight, windowBPP))
	{
		MessageBox(NULL, "Unable to create window", "Error", MB_ICONERROR | MB_OK);
		windowMng->destroyWND();
		return 1;
	}

	if (!oglWindow.initOGL(screenWidth, screenHeight))
	{
		MessageBox(NULL, "Could not launch app", "An error occurred", MB_ICONERROR | MB_OK);
		windowMng->destroyWND(); 
		return 1;
	}

	inputMng->clearBuffers(inputMng->KEYS_DOWN_BUFFER | inputMng->KEYS_PRESSED_BUFFER);

	LPCSTR gameSounds[1] = { "Audio\\Space_Coast.mp3" };

	soundMng->add("MenuMusic", gameSounds[0]);

	//LPCSTR objectTextures[] = {};

	introTex.createTexture("Images\\intro_screen.png");
	introSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	introSprite.setTexture(introTex.getTexture());
	introSprite.setTextureDimensions(introTex.getTWidth(), introTex.getTHeight());

	backGroundTex.createTexture("Images\\game_background.png");
	backGroundSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	backGroundSprite.setTexture(backGroundTex.getTexture());
	backGroundSprite.setTextureDimensions(backGroundTex.getTWidth(), backGroundTex.getTHeight());

	charTex.createTexture("Images\\knight.png");
	charSprite.setSpritePos(glm::vec2(50.0f, 180.0f));
	charSprite.setTexture(charTex.getTexture());
	charSprite.setTextureDimensions(charTex.getTWidth(), charTex.getTHeight());

	swordTex.createTexture("Images\\Sword_Sprite.png");
	swordSprite.attachInputMgr(inputMng);
	swordSprite.setSpritePos(glm::vec2(200.0f, 290.0f));
	swordSprite.setTexture(swordTex.getTexture());
	swordSprite.setTextureDimensions(swordTex.getTWidth(), swordTex.getTHeight());

	tempObjectTex.createTexture("Images\\Ball.png");
	objectSprite1.attachInputMgr(inputMng);
	objectSprite1.setSpritePos(glm::vec2(1280.0f, 300.0f));
	objectSprite1.setTexture(tempObjectTex.getTexture());
	objectSprite1.setTextureDimensions(tempObjectTex.getTWidth(), tempObjectTex.getTHeight());

	introSprite.attachSoundMgr(soundMng);
	int game_State = MENU;

	soundMng->getSnd("MenuMusic")->playAudio(AL_LOOPING);
	
	while (windowMng->isWNDRunning())
	{
		windowMng->processWNDEvents();

		float timeSince = windowMng->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//introSprite.render();

		switch (game_State)
		{
		case MENU:
		{
			introSprite.render();
			if (inputMng->wasKeyPressed(VK_RETURN))
			{
				game_State = PLAYING;
				soundMng->getSnd("MenuMusic")->stopAudio();
			}
			break;
		}
		case PLAYING:
		{
			backGroundSprite.render();
			charSprite.render();
			swordSprite.update(timeSince);
			swordSprite.render();
			objectSprite1.update(timeSince);
			objectSprite1.render();
			// main game code in here
			// When game finished change game_State to END.
			break;
		}
		case END:
		{
			// end sprite render
			// if replaying change game_State to PLAYING
			break;
		}
		}


		windowMng->swapBuffers();
		inputMng->clearBuffers(inputMng->KEYS_DOWN_BUFFER | inputMng->KEYS_PRESSED_BUFFER);
	}

	oglWindow.shutdown();
	windowMng->destroyWND();

	return 0;
}