/*****************************************************************
 * \file	ButtonInterface.hpp
 * \brief	Header is for class ButtonInterface, to be used with ButtonInterface.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <SFML/Window/Event.hpp>
#include <map>

namespace sf {
	class RenderWindow;
}

/**
 * @brief ButtonInterface class used to interface buttons to be rendered on a window
 * and enables reactions to window events, with non parameter specific callbacks funtions.
 */
class ButtonInterface
{
public:

	/**
	 * @brief Constructor, sets the args map to nullptr.
	 */
	ButtonInterface();

	/**
	 * @brief Default destructor.
	 */
	~ButtonInterface() = default;

	/**
	 * @brief Method to be called on a window event
	 * @param window The window object reference.
	 * @param evnt Event type occured on the window
	 */
	virtual void onWindowEvent(sf::RenderWindow* window, const sf::Event& evnt) = 0;

	/**
	 * @brief Method which sets the click callback, in case it's called inside onWindowEvent.
	 * @param callback A function pointer.
	 * @param argsMap The function's arguments map.
	 * @see onWindowEvent()
	 */
	virtual void setClickCallback(void (*callback)(std::map<std::string, void*>), const std::map<std::string, void*>& argsMap);

protected:

	/**
	 * @brief Holds the callback function to be called when setClickCallback is evoked.
	 * @see setClickCallback()
	 */
	void (*p_clickCallback)(std::map<std::string, void*>);

	/**
	 * @brief Holds the parameters of the callback function to be called when setClickCallback is evoked.
	 * @see setClickCallback()
	 */
	std::map<std::string, void*> p_clickCallbackArgsMap;
};