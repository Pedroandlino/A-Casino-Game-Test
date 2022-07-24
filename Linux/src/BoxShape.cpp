/*****************************************************************
 * \file	BoxShape.cpp
 * \brief	Functions and methods for class BoxShape, to be used with BoxShape.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "BoxShape.hpp"
#include <boost/shared_ptr.hpp>

BoxShape::BoxShape(const sf::Vector2f& pos,
	const sf::Vector2f& size, const sf::Color& backgroundColor) :
	p_textureActive(false)
{
	//setup rectangle:
	p_rectangleShape.setPosition(pos);
	p_rectangleShape.setSize(size);
	p_rectangleShape.setOrigin({ size.x / 2,size.y / 2 });
	p_rectangleShape.setFillColor(backgroundColor);
}

BoxShape::BoxShape(const sf::Vector2f& pos,
	const sf::Vector2f& size, const std::string& path) :
	p_textureActive(true)
{
	//setup rectangle:
	p_rectangleShape.setPosition(pos);
	p_rectangleShape.setSize(size);
	p_rectangleShape.setOrigin({ size.x / 2,size.y / 2 });
	setTexture(path, Mask0, true);
}

void BoxShape::setTexture(const std::string& path, TextureMask mask, bool activate)
{
	//allocate
	p_textureMap[mask] = boost::shared_ptr<sf::Texture>(new sf::Texture);
	p_currentMask = mask;
	if (p_textureMap[mask]->loadFromFile(path)) {

		if (activate) {
			enableTexture(activate);
		}
	}
	else {
		throw("CAN'T LOAD TEXTURE: " + path);
	}
}

void BoxShape::swapTexture(TextureMask mask) {
	if (p_textureMap.count(mask) != 0 && p_currentMask != mask) {
		p_currentMask = mask;
		enableTexture(p_textureActive);
	}
}


void BoxShape::enableTexture(bool enable) {
	if (p_textureMap[p_currentMask] != nullptr) {
		if (enable) {
			if (p_rectangleShape.getFillColor() == sf::Color::Transparent) {
				p_rectangleShape.setFillColor(sf::Color::White);
			}
			p_rectangleShape.setTexture(p_textureMap[p_currentMask].get());
			
			//TODO: set new methods for setTextureRect() interface
		}
		p_textureActive = enable;
	}
}

void BoxShape::resetPositon(const sf::Vector2f& pos)
{
	p_rectangleShape.setPosition(pos);
}

void BoxShape::drawTo(sf::RenderWindow* window)
{
	if (window != nullptr) {
		window->draw(p_rectangleShape);
	}
}

void BoxShape::rotate(float degrees) {

	p_rectangleShape.setRotation(degrees);
}

void BoxShape::scale(const sf::Vector2f& scale) {

	p_rectangleShape.setScale(scale);
}