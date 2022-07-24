/*****************************************************************
 * \file	CustomSound.cpp
 * \brief	Functions and methods for class CustomSound, to be used with CustomSound.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "CustomSound.hpp"

CustomSound::CustomSound(const std::string& path)
{
	if (!openFromFile(path)) {
		throw("CAN'T LOAD MUSIC: " + path);
	}
}

void CustomSound::uninterruptedPlay()
{
	if (getStatus() != sf::SoundSource::Status::Playing)
	{
		play();
		//warning this function might be unsafe, in case of polling;
	}
}
