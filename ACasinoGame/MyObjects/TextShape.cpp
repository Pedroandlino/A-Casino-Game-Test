/*****************************************************************
 * \file	TextShape.cpp
 * \brief	Functions and methods for class TextShape, to be used with TextShape.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "TextShape.hpp"
#include "CustomSound.hpp"

TextShape::TextShape(const std::string& content, const sf::Vector2f& pos,
	const sf::Vector2f& size, int contentSize, const sf::Color& textColor, const sf::Color& backgroundColor) :
	BoxShape(pos, size, backgroundColor),
	p_updateTextSoundActive(false)
{

	//setup text:
	std::string path = "MyResources/Fonts/arial.ttf";
	resetFont(path);
	p_text.setString(content);

	if (contentSize <= 0) {
		p_text.setCharacterSize((unsigned int)(p_rectangleShape.getLocalBounds().height / 3.0f));
	}
	else {
		p_text.setCharacterSize(contentSize);
	}
	//p_text.setFillColor(textColor);
	float xPos = pos.x - (p_text.getLocalBounds().width / 2);
	float yPos = pos.y - (p_text.getLocalBounds().height);
	p_text.setPosition({ xPos, yPos });
}

void TextShape::resetFont(const std::string& path)
{
	if (!p_font.loadFromFile(path)) {
		throw("CAN'T LOAD FONT: " + path);
	}
	p_text.setFont(p_font);
	p_text.setStyle(sf::Text::Regular);
}

void TextShape::resetPositon(const sf::Vector2f& pos)
{
	p_rectangleShape.setPosition(pos);
	float xPos = pos.x - (p_text.getLocalBounds().width / 2);
	float yPos = pos.y - (p_text.getLocalBounds().height);
	p_text.setPosition({ xPos, yPos });
}

void TextShape::resetContent(const std::string& content)
{
	p_text.setString(content);

	//update position
	float xPos = p_rectangleShape.getPosition().x - (p_text.getLocalBounds().width / 2);
	float yPos = p_rectangleShape.getPosition().y - (p_text.getLocalBounds().height);
	p_text.setPosition({ xPos, yPos });

	//use sound effect
	if (p_updateSound != nullptr && p_updateTextSoundActive) {
		p_updateSound->play();
	}
}
void TextShape::setUpdateSound(const std::string& path, bool activate)
{
	p_updateSound.reset(new CustomSound(path));
	enableTextUpdateSound(activate);
}
void TextShape::enableTextUpdateSound(bool enable) {
	p_updateTextSoundActive = enable;
}

void TextShape::drawTo(sf::RenderWindow* window)
{
	if (window != nullptr) {
		window->draw(p_rectangleShape);
		window->draw(p_text);
	}
}