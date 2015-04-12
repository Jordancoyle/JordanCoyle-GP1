
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

	cTexture backGround;

	cBkGround backGroundSprite;

	windowOGL oglWindow;

	static cWNDManager* windowMng = cWNDManager::getInstance();
	static cSoundMgr* soundMng = cSoundMgr::getInstance();

	windowMng->attachOGLWnd(&oglWindow);

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

	backGround.createTexture("Images\\intro_screen.png");
	backGroundSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	backGroundSprite.setTexture(backGround.getTexture());
	backGroundSprite.setTextureDimensions(backGround.getTWidth(), backGround.getTHeight());

	backGroundSprite.attachSoundMgr(soundMng);

	while (windowMng->isWNDRunning())
	{
		windowMng->processWNDEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		backGroundSprite.render();

		windowMng->swapBuffers();
	}

	return 0;
}