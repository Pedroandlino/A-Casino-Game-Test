/*****************************************************************
 * \file	CasinoGame.hpp
 * \brief	Header is for class CasinoGame, to be used with CasinoGame.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <map>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <boost/shared_ptr.hpp>

#include "CustomSound.hpp"

class WindowModel;
class WindowInterface;
class ButtonInterface;
class ParticleInterface;

/**
 * @brief CasinoGame class used to run and handle all the variables necessary
 * to run a casino game object, from initialization to communication between objects on window evets.
 */
class CasinoGame
{
public:

	/**
	 * @brief Structure which holds the properties that define the current game state variables.
	 */
	struct State {
		/** @brief Holds the play count. */
		unsigned int playCount;
		/** @brief Holds the inserted plays count. */
		unsigned int insertCount;
		/** @brief Holds the removed plays count. */
		unsigned int removeCount;
		/** @brief Holds the physics paused value, true if it is paused. */
		bool physicsPaused;
		/** @brief Holds the play ongoing value, true if the play is ongoing. */
		bool playOngoing;

		/**
		 * @brief Default constructor.
		 */
		State() {
			playCount = 0;
			insertCount = 0;
			removeCount = 0;
			physicsPaused = false;
			playOngoing = false;
		}

		/**
		 * @brief Constructor.
		 * @param playCount_  Inputs a play count value
		 * @param insertCount_ Inputs a inserted count value
		 * @param removeCount_ Inputs a removed count value
		 * @param physicsPaused_ Inputs a physics paused flag
		 * @param playOngoing_ Inputs a play ongoing flag
		 */
		State(
			unsigned int playCount_,
			unsigned int insertCount_,
			unsigned int removeCount_,
			bool physicsPaused_,
			bool playOngoing_)
		{
			playCount = playCount_;
			insertCount = insertCount_;
			removeCount = removeCount_;
			physicsPaused = physicsPaused_;
			playOngoing = playOngoing_;
		}
	};

	/**
	 * @brief Constructor.
	 * @param windowModel The window model to run the game on.
	 */
	CasinoGame(boost::shared_ptr<WindowModel> windowModel);

	/**
	 * @brief Default destructor.
	 */
	~CasinoGame() = default;

	/**
	 * @brief Method which runs all the necessary initialization functions to instatiate the game.
	 */
	void init();

	/**
	 * @brief Method which switches the render window of the game and re-instatiates it.
	 * @param window The window object reference.
	 * @see WindowInterface
	 */
	 //WARNING: Not tested
	void switchToWindow(boost::shared_ptr<WindowModel> windowModel);

	/**
	 * @brief Method which, when called, updates the buttons according to an event.
	 * @param evnt The window event.
	 * @see WindowInterface
	 */
	void updateButtonsOnWindowEvent(const sf::Event& evnt);

	/**
	 * @brief Method which updates the physics of the internal particles on \pm_particleMap
	 * based on deltaTime.
	 * @param deltaTime The time interval to update the differential equations.
	 */
	void updatePhysics(float deltaTime);

	/**
	 * @brief Method which gives access to the window running the game (not the owner).
	 */
	WindowModel* getCurrentWindow();

private:
	/**
	 * @brief Method which loads a game state.
	 */
	void loadState();

	/**
	 * @brief Method which initializes the game environment music.
	 */
	void initMusic();

	/**
	 * @brief Method which initializes the game background textures.
	 */
	void initBackground();

	/**
	 * @brief Method which initializes the static texts objects.
	 */
	void initStaticTexts();

	/**
	 * @brief Method which initializes the dynamic texts objects.
	 */
	void initDynamicTexts();

	/**
	 * @brief Method which initializes the particle objects.
	 */
	void initParticleObjects();

	/**
	 * @brief Method which initializes the button objects.
	 */
	void initButtons();

	/**
	 * @brief Method which connects the particle objects with their running callbacks and arguments.
	 */
	void connectParticleObjects();

	/**
	 * @brief Method which connects the button objects with their running callbacks and arguments.
	 */
	void connectButtons();

	/**
	 * @brief Method which adds all the shapes initialized to be rendered on the window, by layer order.
	 */
	void addShapesToWindow();

	/**
	 * @brief Static method, to be used as a callback function pointer, which handles a start button click event.
	 */
	static void onStartButton(std::map<std::string, void*> argsMap);

	/**
	 * @brief Static method, to be used as a callback function pointer, which handles a credits inserted button click event.
	 */
	static void onCreditsInButton(std::map<std::string, void*> argsMap);

	/**
	 * @brief Static method, to be used as a callback function pointer, which handles a credits removed button click event.
	 */
	static void onCreditsOutButton(std::map<std::string, void*> argsMap);

	/**
	 * @brief Static method, to be used as a callback function pointer, which handles a particle death verification event.
	 */
	static bool particleDeathCondition(std::map<std::string, void*> argsMap);

	/** @brief Holds the \pm_currentWindow size */
	sf::Vector2f m_winSize;

	/** @brief Holds the map of WindowInterface references, one for each allocated shape, and its render layer (is the owner). */
	std::map<std::string, std::pair<boost::shared_ptr<WindowInterface>, int>> m_shapeMap;

	/** @brief Holds the map of ButtonInterface references, one for each allocated button (is the owner). */
	std::map<std::string, boost::shared_ptr<ButtonInterface>> m_buttonMap;

	/** @brief Holds the map of ParticleInterface references, one for each allocated particle (is the owner). */
	std::map<std::string, boost::shared_ptr<ParticleInterface>> m_particleMap;

	/** @brief Holds the current window pointer, to where game is supposed to be currently being rendered to. */
	boost::shared_ptr<WindowModel> m_currentWindow;

	/** @brief Holds the current game state. */
	State m_currentState;

	/** @brief Holds the map of CustomSound references, one for each allocated particle (is the owner). */
	std::map<std::string, boost::shared_ptr<CustomSound>> m_soundMap;

	/** @brief Holds the numebr of particles to be generated. */
	int m_numberOfParticleToGenerate; //TODO: consider movint this to the game state
};