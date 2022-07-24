/*****************************************************************
 * \file	WindowInterface.hpp
 * \brief	Header is for class WindowInterface, to be used with WindowInterface.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

namespace sf {
	class RenderWindow;
}

/**
 * @brief WindowInterface class is an interface to enable objects to be rendered
 * to be drawn to a specific window, the idea is that the window can call objects with this interface
 * to render them when they're supposed to be rendered.
 */
class WindowInterface
{
public:
	/**
	 * @brief Default constructor.
	 */
	WindowInterface() = default;

	/**
	 * @brief Default destructor.
	 */
	~WindowInterface() = default;

	/**
	 * @brief Method which draws a shape to a specific window.
	 * @param window The window object reference.
	 */
	virtual void drawTo(sf::RenderWindow* window) = 0;

};