
#include "cWNDManager.h"
#include "windowOGL.h"
#include "GameConstants.h"
#include "knightSlash.h"
#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevHInstance, LPSTR cmdLine, int cmdShow)
{
	const int screenWidth = 1600,
		screenHeight = 720,
		windowBPP = 16;

	cTexture introTex,
		backGroundTex;

	cBkGround introSprite,
		backGroundSprite;

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

	introTex.createTexture("Images\\intro_screen.png");
	introSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	introSprite.setTexture(introTex.getTexture());
	introSprite.setTextureDimensions(introTex.getTWidth(), introTex.getTHeight());

	backGroundTex.createTexture("Images\\game_background.png");
	backGroundSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	backGroundSprite.setTexture(backGroundTex.getTexture());
	backGroundSprite.setTextureDimensions(backGroundTex.getTWidth(), backGroundTex.getTHeight());

	introSprite.attachSoundMgr(soundMng);

	while (windowMng->isWNDRunning())
	{
		windowMng->processWNDEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		introSprite.render();

		if (inputMng->anyKeyPressed() == true)
		{
			//windowMng->processWNDEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
			//introSprite.setActive(false);
			backGroundSprite.render();

			windowMng->swapBuffers();
			//inputMng->clearBuffers(inputMng->KEYS_DOWN_BUFFER | inputMng->KEYS_PRESSED_BUFFER);
		}

		windowMng->swapBuffers();
		inputMng->clearBuffers(inputMng->KEYS_DOWN_BUFFER | inputMng->KEYS_PRESSED_BUFFER);
	}

	oglWindow.shutdown();
	windowMng->destroyWND();

	return 0;
}