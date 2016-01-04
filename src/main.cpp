#define UNUSED_VARIABLE(x) (void)x

#include "GameData.h"
#include "GameManager.h"
#include "IntroState.h"
#include "MenuState.h"
#include "LoadLevelState.h"
//#include "PlayState.h"
//#include "PauseState.h"
//#include "EndGameState.h"
//#include "CreditsState.h"
//#include "RecordsState.h"

#include <iostream>

using namespace std;

int main ()
{
	GameData* gameData				= new GameData();
	GameManager* game 				= new GameManager();
	IntroState* introState 			= new IntroState();
	MenuState* menuState 			= new MenuState();
	LoadLevelState *loadLevelState 	= new LoadLevelState();
//	PlayState* playState		= new PlayState();
//	PauseState* pauseState 		= new PauseState();
//	EndGameState* endState		= new EndGameState();
//	CreditsState* creditsState	= new CreditsState();
//	RecordsState* recordsState	= new RecordsState();

	UNUSED_VARIABLE(gameData);
	UNUSED_VARIABLE(game);
	UNUSED_VARIABLE(introState);
	UNUSED_VARIABLE(menuState);
	UNUSED_VARIABLE(loadLevelState);
	//UNUSED_VARIABLE(playState);
	//UNUSED_VARIABLE(pauseState);
	//UNUSED_VARIABLE(endState);
	//UNUSED_VARIABLE(creditsState);
	//UNUSED_VARIABLE(recordsState);

	try
	{
		// Inicializa el juego y transición al primer estado.
		game->start(IntroState::getSingletonPtr());
	}
	catch (Ogre::Exception& e)
	{
		std::cerr << "Excepción detectada: " << e.getFullDescription();
	}

	delete gameData;
	delete game;
//	delete introState;
//	delete menuState;
//	delete loadLevelState;

	return 0;
}
