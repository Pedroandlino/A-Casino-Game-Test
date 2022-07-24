/*****************************************************************
 * \file	ButtonShape.hpp
 * \brief	Header is for class ButtonShape, to be used with ButtonShape.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include "TextShape.hpp"
#include "ButtonInterface.hpp"
#include <boost/shared_ptr.hpp>

class CustomSound;

/**
 * @brief ButtonShape class used to handle button common behaviours
 * buttons consists TextShapes with ButtonInterface.
 */
class ButtonShape : public TextShape, public ButtonInterface
{
public:
	/**
	 * @brief Type which identifies the state of the button.
	 */
	enum State {
		None,
		Inside,
		Outside
	};

	/**
	 * @brief Constructor.
	 * @param text The text to be written of the button.
	 * @param pos The position of the button.
	 * @param size The size of the button.
	 * @param backgroundColor The base color of the button.
	 * @param textColor The base color of the button.
	 * @param textSize The size of the font to be written using \ptext.
	 */
	ButtonShape(
		const std::string& text,
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		const sf::Color& backgroundColor,
		const sf::Color& textColor,
		int textSize = -1);

	/**
	 * @brief Default destructor.
	 */
	~ButtonShape() = default;

	/**
	 * @brief Method which checks if the mouse position on window is over the current object rectagle area
	 * warning: this function assumes the object isn't rotated.
	 * @param window The window object reference.
	 * @return The value of true if the mouse on current window is over the button.
	 */
	bool isMouseOver(sf::RenderWindow* window);

	/**
	 * @brief Method which draws the button object,and its compositors to the window.
	 * @param window The window object reference.
	 * @see WindowInterface
	 */
	virtual void drawTo(sf::RenderWindow* window) override;

	/**
	 * @brief Method which gets the current internal state of the button.
	 * @return The current internal state of the button.
	 */
	State getState();

	/**
	 * @brief Method which checks if the current internal state of the button has changed.
	 * @return The value of true if the current internal state of the button changed.
	 */
	bool toggled();

	/**
	 * @brief Method which is to be called when a window event occurs on the ButtonInterface
	 * @param window The window object reference.
	 * @param evnt Event type occured on the window.
	 * @see ButtonInterface
	 */
	virtual void onWindowEvent(sf::RenderWindow* window, const sf::Event& evnt) override;

	/**
	 * @brief Method which sets and loads the hover behaviour sound.
	 * @param path The path of the sound to be played.
	 * @param activate If the sound should start active.
	 */
	void setHoverSound(const std::string& path, bool activate = true);

	/**
	 * @brief Method which sets and loads the click behaviour sound.
	 * @param path The path of the sound to be played.
	 * @param activate If the sound should start active.
	 */
	void setClickSound(const std::string& path, bool activate = true);

	/**
	 * @brief Method which sets if the hover should be played.
	 * @param enable The value to enable the playing of the sound.
	 */
	void enableHoverSound(bool enable);

	/**
	 * @brief Method which sets if the click should be played.
	 * @param enable The value to enable the playing of the sound.
	 */
	void enableClickSound(bool enable);

private:

	/** @brief Holds the composing Color object, responsible for the background color. */
	const sf::Color m_backgroundColor;

	/** @brief Holds the current internal state of thebutton. */
	State m_state;

	/** @brief Holds the flag value, true if the button state was toggled. */
	bool m_toggled;

	/** @brief Holds the CustomSound reference for the hover sound, if it is allocated. */
	boost::shared_ptr<CustomSound> m_hoverSound;

	/** @brief Holds the CustomSound reference for the click sound, if it is allocated. */
	boost::shared_ptr<CustomSound> m_clickSound;

	/** @brief Holds the flag value, true if the hover sound is active. */
	bool m_hoverSoundActive;

	/** @brief Holds the flag value, true if the click sound is active. */
	bool m_clickSoundActive;
};