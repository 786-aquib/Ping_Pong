#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;
	_mainWindow.Create(sf::VideoMode(1024,768,32),"Pang!");
	PlayerPaddle *player1 = new PlayerPaddle();
	player1->Load("images/paddle.png");
	player1->SetPosition((1024/2)-45,700);
	_gameObjectManager.Add("Paddle1",player1);
	_gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);
	
	
	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{
				_mainWindow.Clear(sf::Color(0,0,0));

				_gameObjectManager.DrawAll(_mainWindow);

				_mainWindow.Display();
				if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;

				if(currentEvent.Type == sf::Event::KeyPressed)
					{
						if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
					}

				break;
			}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Exiting;
			break;
		case MainMenu::Play:
			_gameState = Playing;
			break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;