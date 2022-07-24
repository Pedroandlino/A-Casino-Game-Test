/*****************************************************************
 * \file	ButtonInterface.cpp
 * \brief	Functions and methods for class ButtonInterface, to be used with ButtonInterface.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "ButtonInterface.hpp"

ButtonInterface::ButtonInterface() : p_clickCallback(nullptr) {};

void ButtonInterface::setClickCallback(
	void (*callback)(std::map<std::string, void*>),
	const std::map<std::string, void*>& argsMap)
{
	p_clickCallback = callback;
	p_clickCallbackArgsMap = argsMap;
}

