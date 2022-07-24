/*****************************************************************
 * \file	Main.cpp
 * \brief	Main cpp, from where main() is executed to run 'ACasinoGame'
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "MyObjects/WindowManager.hpp"
#include "MyObjects/CasinoGame.hpp"
#include "MyObjects/WindowModel.hpp"

#include <memory>
#include <iostream>


int main() {

	std::cout << "'ACasinoGame' has started!\n";

	//window init:
	int fps = 60;
	float deltaTimeS = 1 / float(fps);
	WindowManager::createWindow("A Casino Game", sf::Vector2u(800, 600), fps, "MyResources/Icons/ACasinoGame.png");
	std::shared_ptr<WindowModel> windowModel = WindowManager::getWindowModel("A Casino Game");

	//game init
	CasinoGame aCasinoGame(windowModel);
	aCasinoGame.init();


	//Game Loop:
	while (aCasinoGame.getCurrentWindow()->isOpen())
	{
		//update physics on window
		aCasinoGame.updatePhysics(deltaTimeS);

		sf::Event evnt;
		while (aCasinoGame.getCurrentWindow()->pollEvent(evnt))
		{
			aCasinoGame.updateButtonsOnWindowEvent(evnt);

			switch (evnt.type) {
			case sf::Event::Closed:
				windowModel->close();
				break;
			}
		}

		//update window:
		aCasinoGame.getCurrentWindow()->clear(); //clear render
		aCasinoGame.getCurrentWindow()->drawChildren(); //draw loaded children
		aCasinoGame.getCurrentWindow()->display(); //rasterize to render
	}

	std::cout << "'ACasinoGame' has quit gracefully.\n";
	std::cout << "Until the next time.\n";

	return 0;
}