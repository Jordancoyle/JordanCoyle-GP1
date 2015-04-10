
#include "cWNDManager.h"
#include "windowOGL.h"
#include <Windows.h>


int WINAPI mainWin(HINSTANCE hInstance, HINSTANCE prevHInstance, LPSTR cmdLine, int cmdShow)
{
	const int screenWidth = 1600;
	const int screenHeight = 720;
	const int windowBPP = 16;

	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	return 0;
}