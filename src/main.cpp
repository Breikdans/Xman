#define UNUSED_VARIABLE(x) (void)x

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
	GameManager* game 			= new GameManager();
	IntroState* introState 		= new IntroState();
	MenuState* menuState 		= new MenuState();
	LoadLevelState *loadLevelState = new LoadLevelState();
//	PlayState* playState		= new PlayState();
//	PauseState* pauseState 		= new PauseState();
//	EndGameState* endState		= new EndGameState();
//	CreditsState* creditsState	= new CreditsState();
//	RecordsState* recordsState	= new RecordsState();

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

	delete game;

	return 0;
}
