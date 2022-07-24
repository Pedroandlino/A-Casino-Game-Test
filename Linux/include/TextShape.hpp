/*****************************************************************
 * \file	TextShape.hpp
 * \brief	Header is for class TextShape, to be used with TextShape.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include "BoxShape.hpp"
#include <boost/shared_ptr.hpp>

class CustomSound;

/**
 * @brief TextShape class purpose is to initilize BoxShapes with texts within
 * it can be used without a texture, therefore displaying only the text when its shape is rendered.
 */
class TextShape : public BoxShape
{
public:

	/**
	 * @brief Constructor.
	 * @param content The text to be written.
	 * @param pos The position of the text.
	 * @param size The size of the text container area.
	 * @param contentSize The size of text font.
	 * @param textColor The color of the text.
	 * @param backgroundColor The base color of the text container area.
	 */
	TextShape(
		const std::string& content,
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		int contentSize = 0,
		const sf::Color& textColor = sf::Color::White,
		const sf::Color& backgroundColor = sf::Color::Transparent);

	/**
	 * @brief Default destructor.
	 */
	~TextShape() = default;

	/**
	 * @brief Method which resets the text font by loading another
	 * @param path The path of the font to be loaded.
	 */
	void resetFont(const std::string& path);

	/**
	 * @brief Method which resets the position of the shape to a new position.
	 * @param pos The new position coordinate.
	 */
	virtual void resetPositon(const sf::Vector2f& pos) override;

	/**
	 * @brief Method which resets the text content of the text being displayed.
	 * @param content The text content.
	 */
	virtual void resetContent(const std::string& content);

	/**
	 * @brief Method which sets and loads the text update behaviour sound.
	 * @param path The path of the sound to be played.
	 * @param activate If the sound should start active.
	 */
	void setUpdateSound(const std::string& path, bool activate = true);

	/**
	 * @brief Method which sets if the text update sound should be played.
	 * @param enable The value to enable the playing of the sound.
	 */
	void enableTextUpdateSound(bool enable);

	/**
	 * @brief Method which draws the text object,and its compositors to the window.
	 * @param window The window object reference.
	 * @see WindowInterface
	 */
	virtual void drawTo(sf::RenderWindow* window) override;

protected:
	/** @brief Holds the composing Text object. */
	sf::Text p_text;

	/** @brief Holds the composing Font object. */
	sf::Font p_font;

	/** @brief Holds the CustomSound reference for the text update sound, if it is allocated. */
	boost::shared_ptr<CustomSound> p_updateSound;

	/** @brief Holds the flag value, true if the text update sound is active. */
	bool p_updateTextSoundActive;
};