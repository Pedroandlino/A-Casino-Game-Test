/*****************************************************************
 * \file	WindowModel.hpp
 * \brief	Header is for class WindowModel, to be used with WindowModel.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <boost/shared_ptr.hpp>

class WindowInterface;
class ButtonInterface;

/**
 * @brief WindowModel class inherits RenderWindow so that more functionalities and interfaces
 * can be added to each window objects. Some of the main functionalities of this class are:
 * holding the renference to objects that can be rendered, rendering these objects on calling drawChildren()
 * render them by layer order to pass OpenGL Z-Buffer Test.
 */
class WindowModel : public sf::RenderWindow
{
public:
	/**
	 * @brief Type which identifies the OpenGL Z-test render layer.
	 */
	enum Layer {
		l0,
		l1,
		l2,
		l3,
		l4,
		l5
	};

	/**
	 * @brief Constructor.
	 * @param title The title of the renderer window.
	 * @param size The size of the renderer.
	 */
	WindowModel(const std::string& title, const sf::Vector2u& size);

	/**
	 * @brief Default destructor.
	 */
	~WindowModel();

	/*
	* @brief Function called after the window has been resized
	* This function is called so that derived classes can
	* perform custom actions when the size of the window changes.
	*/
	void onResize() override;

	/**
	 * @brief Method which adds a child shape to be rendered on window.
	 * @param child The child shape of WindowInterface type.
	 */
	void addChild(boost::shared_ptr<WindowInterface> child);

	/**
	 * @brief Method which adds a child button to be rendered on window.
	 * @param buttons The child shape of ButtonInterface type.
	 */
	void removeButtons(std::vector<boost::shared_ptr<ButtonInterface>> buttons);

	/**
	 * @brief Method which draws the children shapes of type WindowInterface.
	 */
	void drawChildren();

private:
	/** @brief Holds the original window size from when WindowModel was created. */
	const sf::Vector2u m_originalSize;

	/** @brief Holds the vector of WindowInterface references (not the owner). */
	std::vector<boost::shared_ptr<WindowInterface>> m_children;

	/** @brief Holds the vector of ButtonInterface references (not the owner). */
	std::vector<boost::shared_ptr<ButtonInterface>> m_buttons;
};