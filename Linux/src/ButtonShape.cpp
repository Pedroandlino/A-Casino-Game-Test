/*****************************************************************
 * \file	ButtonShape.cpp
 * \brief	Functions and methods for class ButtonShape, to be used with ButtonShape.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "ButtonShape.hpp"
#include "CustomSound.hpp"

ButtonShape::ButtonShape(const std::string& text, const sf::Vector2f& pos,
	const sf::Vector2f& size, const sf::Color& backgroundColor, const sf::Color& textColor, int textSize) :
	TextShape(text, pos, size, textSize, textColor, backgroundColor),
	m_backgroundColor(backgroundColor),
	m_state(ButtonShape::State::None),
	m_toggled(false),
	m_hoverSoundActive(false),
	m_clickSoundActive(false)
{
	resetFont("MyResources/Fonts/arialbd.ttf");
}

bool ButtonShape::isMouseOver(sf::RenderWindow* window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

	sf::Vector2f rectPos = p_rectangleShape.getPosition();

	float rectMarginX = p_rectangleShape.getLocalBounds().width / 2;
	float rectMarginY = p_rectangleShape.getLocalBounds().height / 2;

	if (rectPos.x - rectMarginX < mousePos.x && mousePos.x < rectPos.x + rectMarginX &&
		rectPos.y - rectMarginY < mousePos.y && mousePos.y < rectPos.y + rectMarginY)
	{
		sf::Color highLightColor = m_backgroundColor;
		(highLightColor.r + 200 > 255) ? highLightColor.r = 255 : highLightColor.r += 200;
		(highLightColor.g + 200 > 255) ? highLightColor.g = 255 : highLightColor.g += 200;
		(highLightColor.b + 200 > 255) ? highLightColor.b = 255 : highLightColor.b += 200;
		p_rectangleShape.setFillColor(highLightColor);

		if (m_state != Inside) {
			m_state = Inside;
			m_toggled = true;
		}
		else {
			m_toggled = false;
		}
		return true;
	}
	else {
		p_rectangleShape.setFillColor(m_backgroundColor);
		if (m_state != Outside) {
			m_state = Outside;
			m_toggled = true;
		}
		else {
			m_toggled = false;
		}
		return false;
	}
}

void ButtonShape::drawTo(sf::RenderWindow* window)
{
	if (window != nullptr) {
		window->draw(p_rectangleShape);
		window->draw(p_text);
	}
}

ButtonShape::State ButtonShape::getState()
{
	return m_state;
}

bool ButtonShape::toggled()
{
	return m_toggled;
}

void ButtonShape::onWindowEvent(sf::RenderWindow* window, const sf::Event& evnt)
{
	switch (evnt.type) {
	case sf::Event::MouseMoved:
		if (isMouseOver(window)) {
			//hover sound:
			if (getState() == ButtonShape::Inside && toggled() &&
				m_hoverSound != nullptr && m_hoverSoundActive) {
				m_hoverSound->uninterruptedPlay();
			}
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (isMouseOver(window)) {
			//click sound:
			if (m_clickSound != nullptr && m_clickSoundActive) {
				m_clickSound->play();
			}

			//callback:
			if (p_clickCallback != nullptr) {
				p_clickCallback(p_clickCallbackArgsMap);
			}
		}
		break;
	}
}

void ButtonShape::setHoverSound(const std::string& path, bool activate)
{
	m_hoverSound.reset(new CustomSound(path));
	if (activate) {
		enableHoverSound(activate);
	}
}

void ButtonShape::enableHoverSound(bool enable) {
	m_hoverSoundActive = enable;
}

void ButtonShape::setClickSound(const std::string& path, bool activate)
{
	m_clickSound.reset(new CustomSound(path));
	if (activate) {
		enableClickSound(activate);
	}
}

void ButtonShape::enableClickSound(bool enable) {
	m_clickSoundActive = enable;
}