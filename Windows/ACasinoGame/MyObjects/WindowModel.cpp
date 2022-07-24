/*****************************************************************
 * \file	WindowModel.cpp
 * \brief	Functions and methods for class WindowModel, to be used with WindowModel.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/


#include "WindowModel.hpp"
#include "WindowInterface.hpp"
#include "ButtonInterface.hpp"

WindowModel::WindowModel(const std::string& title, const sf::Vector2u& size) :
	sf::RenderWindow(sf::VideoMode(size), title,
		sf::Style::Close | sf::Style::Titlebar), //TODO: | sf::Style::Resize no resize, for now!
	m_originalSize(size)
{
	sf::View view({ 0.5f * size.x, 0.5f * size.y }, { float(size.x), float(size.y) });
	this->setView(view);
}

WindowModel::~WindowModel()
{}

void WindowModel::onResize()
{
	//TODO: setup responsivity of the Window
	/*float originalAR = m_originalSize.x / float(m_originalSize.y);

	sf::View view = this->getView();
	view.setSize({ float(this->getSize().x), float(this->getSize().y * originalAR) });
	view.setCenter({ 0.5f * this->getSize().x, 0.5f * this->getSize().y * originalAR });
	this->setView(view);*/

	RenderWindow::onResize();
}

void WindowModel::addChild(std::shared_ptr<WindowInterface> child)
{
	m_children.push_back(child);
}

void WindowModel::removeButtons(std::vector<std::shared_ptr<ButtonInterface>> buttons)
{
	for (std::shared_ptr<ButtonInterface> button : buttons) {
		m_buttons.erase(
			std::remove_if(m_buttons.begin(), m_buttons.end(),
				[button](std::shared_ptr<ButtonInterface> storedButton)
				{return button.get() == storedButton.get(); }));
	}
}

void WindowModel::drawChildren()
{
	for (std::shared_ptr<WindowInterface>& child : m_children) {
		if (child != nullptr) {
			child->drawTo(this);
		}
	}
}