/*****************************************************************
 * \file	CustomSound.hpp
 * \brief	Header is for class CustomSound, to be used with CustomSound.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <string>
#include <map>

#include <SFML/Audio.hpp>

/**
 * @brief CustomSound class which inherits Mucis object, for utility puposes
 * of playing sonds uninterruptly, after play was pressed.
 */
class CustomSound : public sf::Music
{
public:

	/**
	 * @brief Constructor.
	 * @param path The path of the sould to be loaded.
	 */
	CustomSound(const std::string& path);

	/**
	 * @brief Default destructor.
	 */
	~CustomSound() = default;

	/**
	 * @brief Method which plays the sound file only once, until it has finished.
	 */
	void uninterruptedPlay();

private:
};