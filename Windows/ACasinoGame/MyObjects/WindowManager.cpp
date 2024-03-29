/*****************************************************************
 * \file	WindowManager.cpp
 * \brief	Functions and methods for class WindowManager, to be used with WindowManager.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "WindowManager.hpp"
#include "WindowModel.hpp"

#include <SFML/Graphics.hpp>

WindowManager::WindowManager()
{
}

WindowManager& WindowManager::getInstance()
{
	static WindowManager instance;
	return instance;
}

bool WindowManager::createWindow(const std::string& title, const sf::Vector2u& dims, int fps, const std::string& iconPath)
{
	if (getInstance().m_windowModelMap.count(title) == 0) {
		getInstance().m_windowModelMap[title] =
			std::shared_ptr<WindowModel>(new WindowModel(title, dims));

		getInstance().m_windowModelMap[title]->setFramerateLimit(fps);

		if (!iconPath.empty()) {
			sf::Image icon;
			if (icon.loadFromFile(iconPath)) {
				getInstance().m_windowModelMap[title]->setIcon(icon.getSize(), icon.getPixelsPtr());
			}
			else {
				throw("CAN'T LOAD ICON: " + iconPath);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

std::shared_ptr<WindowModel> WindowManager::getWindowModel(const std::string& title)
{
	if (getInstance().m_windowModelMap.count(title) == 0)
	{
		return nullptr;
	}
	else
	{
		return getInstance().m_windowModelMap[title];
	}
}