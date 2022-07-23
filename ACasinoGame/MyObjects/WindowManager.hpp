/*****************************************************************
 * \file	WindowManager.hpp
 * \brief	Header is for class WindowManager, to be used with WindowManager.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <string>
#include <map>
#include <memory>
#include <SFML/System/Vector2.hpp>

class WindowModel;

/**
 * @brief WindowManager class, singleton, manages all WindowModel objects to be run by the application.
 */
class WindowManager {
public:

	/**
	 * @brief Method which gets the instance of WindowManager singleton.
	 * @return The instance of the WindowManager singleton.
	 */
	static WindowManager& getInstance();

	/**
	 * @brief Method which creates/allocates a new window object, to be owned by WindowManager.
	 * @param title The title of the window (unique).
	 * @param dims The dimensions of the window.
	 * @param fps The frames per second of refresh rate.
	 * @return The value true if a window was created, false if the window name already exists.
	 */
	static bool createWindow(const std::string& title, const sf::Vector2u& dims, int fps = 60);

	/**
	 * @brief Method which allows access to the WindowModels owned by WindowManager.
	 * @param title The title of the window (unique).
	 * @return The WindowModel requested by title.
	 */
	static std::shared_ptr<WindowModel> getWindowModel(const std::string& title);

private:
	/**
	 * @brief Default constructor.
	 */
	WindowManager();

	/**
	 * @brief Default destructor.
	 */
	~WindowManager() = default;

	/** @brief Holds the map of WindowModel references, one for each allocated window. */
	std::map<std::string, std::shared_ptr<WindowModel>> m_windowModelMap;
};