/*****************************************************************
 * \file	BoxShape.hpp
 * \brief	Header is for class BoxShape, to be used with BoxShape.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include "WindowInterface.hpp"
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

/**
 * @brief BoxShape class used for rectangular shapes with textures to be rendered.
 */
class BoxShape : public WindowInterface
{

	//TODO: create BaseShape < WindowInterface, and BoxShape < BaseShape
public:

	/**
	 * @brief Type which identifies texture slots.
	 */
	enum TextureMask {
		Mask0,
		Mask1,
		Mask2
	};

	/**
	 * @brief Constructor.
	 * @param pos The position of the BoxShape rectangle.
	 * @param size The size of the BoxShape rectangle.
	 * @param backgroundColor The base color of the rectangle shape.
	 */
	BoxShape(
		const sf::Vector2f& pos,
		const sf::Vector2f& size,
		const sf::Color& backgroundColor);

	/**
	 * @brief Constructor.
	 * @param pos The position of the BoxShape rectangle.
	 * @param size The size of the BoxShape rectangle.
	 * @param path The path the texture to be loaded for the rectangle shape.
	 */
	BoxShape(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& path);

	/**
	 * @brief Default destructor.
	 */
	~BoxShape() = default;

	/**
	 * @brief Method which sets a texture of the rectangle, into a texture slot, and sets
	 * if it should become immedialty active.
	 * @param path The path the texture to be loaded for the rectangle shape.
	 * * @param mask The texture slot.
	 * @param activate Activates the texture.
	 */
	void setTexture(const std::string& path, TextureMask mask = Mask0, bool activate = true);

	/**
	 * @brief Sets a texture present in a slot, to become the active rendered texture.
	 * @param mask The texture slot.
	 */
	void swapTexture(TextureMask mask);

	/**
	 * @brief Method which enables the texture to be rendered over the shape background color.
	 * @param enable The enable flag.
	 */
	void enableTexture(bool enable);

	/**
	 * @brief Method which resets the position of the shape to a new position.
	 * @param pos The new position coordinate.
	 */
	virtual void resetPositon(const sf::Vector2f& pos);

	/**
	 * @brief Method which draws the rectangle shape to a specific window.
	 * @param window The window object reference.
	 */
	virtual void drawTo(sf::RenderWindow* window) override;

	/**
	 * @brief Method which rotates the rectangle shape.
	 * @param degrees The angle to rotate.
	 */
	void rotate(float degrees);

	/**
	 * @brief Method which scales the rectangle shape.
	 * @param scale The scale x,y values to scales the rectangle.
	 */
	void scale(const sf::Vector2f& scale);

protected:

	/** @brief Holds a flag value, true if the texture is active. */
	bool p_textureActive;

	/** @brief Holds the mask value of the current texture slot active. */
	TextureMask p_currentMask;

	/** @brief Holds the composing RectangleShape object. */
	sf::RectangleShape p_rectangleShape;

	/** @brief Holds the map of Texture references, one for each allocated slot. */
	std::map<TextureMask, std::shared_ptr<sf::Texture>> p_textureMap;
};