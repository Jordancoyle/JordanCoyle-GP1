
#include "cWNDManager.h"
#include "windowOGL.h"
#include "GameConstants.h"
#include "knightSlash.h"
#include "cFontMgr.h"
#include <Windows.h>

//main game code
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevHInstance, LPSTR cmdLine, int cmdShow)
{
	//sets window size
	const int screenWidth = 1280,
		screenHeight = 720,
		windowBPP = 16;

	cTexture introTex,
		backGroundTex,
		charTex,
		swordTex,
		endTex,
		temp;

	cBkGround backGroundSprite,
		introSprite,
		endSprite;

	cKnight charSprite;

	cSword swordSprite;

	cObject objectSprite1;

	windowOGL oglWindow;

	static cWNDManager* windowMng = cWNDManager::getInstance();
	static cSoundMgr* soundMng = cSoundMgr::getInstance();
	static cInputMgr* inputMng = cInputMgr::getInstance();
	static cFontMgr* fontMng = cFontMgr::getInstance();

	windowMng->attachOGLWnd(&oglWindow);
	windowMng->attachInputMgr(inputMng);

	//If unable to create window return an error message
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

	//loads game directories into an array
	LPCSTR gameSounds[4] = {"Audio\\Menumusic_converted.wav", "Audio\\GameMusic_converted.wav", "Audio\\209081_lukesharples_blade-slice8_converted.wav", "Audio\\185557_zagi2_funeral-march-outro_converted.wav" };

	//adds sounds to the sound manager using directories from an array
	soundMng->add("MenuMusic", gameSounds[0]);
	soundMng->add("Background", gameSounds[1]);
	soundMng->add("Slash", gameSounds[2]);
	soundMng->add("EndBackground", gameSounds[3]);

	//Creates array and adds font directories
	LPCSTR gameFonts[1] = {"Fonts\\FRSCRIPT.ttf",};

	//Adds fonts to the font manager using the directory array
	fontMng->addFont("ScriptFont", gameFonts[0], 48);

	//creates array which holds texture directories for objects
	LPCSTR objectTextures[] = {"Images\\star.png", "Images\\Ball.png"};

	//Gets the file directories from the array and then creates the textures
	for (int tCount = 0; tCount < 2; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(objectTextures[tCount]);
	}

	//Creates the object sprites using textures from "theGameTextures"
	for (int object = 0; object < 1; object++)
	{
		theObjects.push_back(new cObject);
		theObjects[object]->setSpritePos(glm::vec2(1280.0f, 350.0f));
		theObjects[object]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
		int randObject = rand() % 2;
		theObjects[object]->setTexture(theGameTextures[randObject]->getTexture());
		theObjects[object]->setTextureDimensions(theGameTextures[randObject]->getTWidth(), theGameTextures[randObject]->getTHeight());
		theObjects[object]->setSpriteCentre();
		theObjects[object]->setobjectVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theObjects[object]->setActive(true);
		theObjects[object]->setMdlRadius();
	}

	//Assigns textures to sprites and thier world positions
	introTex.createTexture("Images\\intro_screen.png");
	introSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	introSprite.setTexture(introTex.getTexture());
	introSprite.setTextureDimensions(introTex.getTWidth(), introTex.getTHeight());

	backGroundTex.createTexture("Images\\game_background.png");
	backGroundSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	backGroundSprite.setTexture(backGroundTex.getTexture());
	backGroundSprite.setTextureDimensions(backGroundTex.getTWidth(), backGroundTex.getTHeight());

	charTex.createTexture("Images\\knight.png");
	charSprite.setSpritePos(glm::vec2(130.0f, 320.0f));
	charSprite.setTexture(charTex.getTexture());
	charSprite.setTextureDimensions(charTex.getTWidth(), charTex.getTHeight());

	swordTex.createTexture("Images\\Sword_Sprite.png");
	swordSprite.attachInputMgr(inputMng);
	swordSprite.setSpritePos(glm::vec2(200.0f, 290.0f));
	swordSprite.setTexture(swordTex.getTexture());
	swordSprite.setTextureDimensions(swordTex.getTWidth(), swordTex.getTHeight());

	endTex.createTexture("Images\\end.png");
	endSprite.setSpritePos(glm::vec2(0.0f, 0.0f));
	endSprite.setTexture(endTex.getTexture());
	endSprite.setTextureDimensions(endTex.getTWidth(), endTex.getTHeight());

	introSprite.attachSoundMgr(soundMng);
	backGroundSprite.attachSoundMgr(soundMng);
	endSprite.attachSoundMgr(soundMng);

	int game_State = MENU;
	float timer = 0.0f;
	int randTime = rand() % 3 + 2;

	//plays specified audio
	soundMng->getSnd("MenuMusic")->playAudio(AL_LOOPING);

	//Main code for the window, runs until the window is shut down
	while (windowMng->isWNDRunning())
	{
		windowMng->processWNDEvents();

		float timeSince = windowMng->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (game_State)
		{
		case MENU:
		{
			//renders the sprite onto the screen
			introSprite.render();

			//If the enter button is pressed the game state changes, audio is also switched
			if (inputMng->wasKeyPressed(VK_RETURN))
			{
				soundMng->getSnd("MenuMusic")->stopAudio();
				soundMng->getSnd("Background")->playAudio(AL_LOOPING);
				game_State = PLAYING;
			}
			break;
		}
		case PLAYING:
		{
			backGroundSprite.render();
			charSprite.update(timeSince);
			charSprite.render();
			swordSprite.update(timeSince);
			swordSprite.render();
			
			int health = charSprite.getPlayerHealth();

			//renders the text onto the window
			fontMng->getFont("ScriptFont")->printText((std::string("Score: ") + std::to_string(swordSprite.getScore())).c_str(), glm::vec2(10.0f, 700.0f));
			fontMng->getFont("ScriptFont")->printText((std::string("Health: ") + std::to_string(health)).c_str(), glm::vec2(1100.0f, 700.0f));

			timer += timeSince;

			//randomly creates objects from the object array
			if (timer > randTime)
			{
				theObjects.push_back(new cObject);
				int object = theObjects.size() - 1;
				theObjects[object]->setSpritePos(glm::vec2(1280.0f, 350.0f));
				theObjects[object]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
				int randObject = rand() % 2;
				theObjects[object]->setTexture(theGameTextures[randObject]->getTexture());
				theObjects[object]->setTextureDimensions(theGameTextures[randObject]->getTWidth(), theGameTextures[randObject]->getTHeight());
				theObjects[object]->setSpriteCentre();
				theObjects[object]->setobjectVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
				theObjects[object]->setActive(true);
				theObjects[object]->setMdlRadius();
				timer = 0.0f;
				randTime = rand() % 5 + 2;
			}

			//renders the randomly created object onto the window
			for (int object = 0; object < theObjects.size(); object++)
			{
				if (theObjects[object]->isActive())
				{
					theObjects[object]->update(timeSince);
					theObjects[object]->render();
				}
			}

			//experimental code for playing sound during collision - DO NOT USE
			if (swordSprite.getSound())
			{
				soundMng->getSnd("Slash")->playAudio(AL_LOOPING);
				soundMng->getSnd("Slash")->stopAudio();
			}

			//experimental code used to change the game state after health has dropped - DO NOT USE
			if (health <= 0)
			{
				soundMng->getSnd("Background")->stopAudio();
				soundMng->getSnd("EndBackground")->playAudio(AL_LOOPING);
				game_State = END;
			}
			break;
		}
		case END:
		{
			endSprite.render();
			soundMng->getSnd("EndBackground")->playAudio(AL_LOOPING);

			//restarts the game when enter is pressed
			if (inputMng->wasKeyPressed(VK_RETURN))
			{
				game_State = PLAYING;
			}

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