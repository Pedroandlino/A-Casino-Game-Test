/*****************************************************************
 * \file	PolyParticleShape.cpp
 * \brief	Functions and methods for class PolyParticleShape, to be used with PolyParticleShape.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "PolyParticleShape.hpp"
#include "MathModule.hpp"
#include "CustomSound.hpp"

PolyParticleShape::PolyParticleShape(
	const sf::Vector2f& pos,
	int nPoints,
	float radius,
	const sf::Color& backgroundColor) :
	p_textureActive(false),
	m_isVisible(false),
	m_birthSoundPlayed(false)
{
	//setup convex polygon shape:
	p_convexShape.setPosition(pos);
	p_convexShape.setOrigin({ 0,0 });
	p_convexShape.setFillColor(backgroundColor);

	generatePolygon(nPoints, radius);
}

PolyParticleShape::PolyParticleShape(
	const sf::Vector2f& pos,
	int nPoints,
	float radius,
	const std::string& path) :
	p_textureActive(true),
	m_isVisible(false)
{
	//setup convex polygon shape:
	p_convexShape.setPosition(pos);
	p_convexShape.setOrigin({ radius,radius });
	setTexture(path, true);

	generatePolygon(nPoints, radius);
}

void PolyParticleShape::randomizeColor() {
	unsigned int red = (unsigned int)MathModule::getRandom(20, 255);
	unsigned int green = (unsigned int)MathModule::getRandom(20, 255);
	unsigned int blue = (unsigned int)MathModule::getRandom(20, 255);
	sf::Color color(red, green, blue);
	p_convexShape.setFillColor(color);
}

void PolyParticleShape::setTexture(const std::string& path, bool activate)
{
	//allocate
	p_texture.reset(new sf::Texture);
	if (p_texture->loadFromFile(path)) {

		if (activate) {
			enableTexture(activate);
		}
	}
	else {
		throw("CAN'T LOAD TEXTURE: " + path);
	}
}

void PolyParticleShape::enableTexture(bool enable) {
	if (p_texture != nullptr) {
		if (enable) {
			if (p_convexShape.getFillColor() == sf::Color::Transparent) {
				p_convexShape.setFillColor(sf::Color::White);
			}
			p_convexShape.setTexture(p_texture.get());
		}
		p_textureActive = enable;
	}
}

void PolyParticleShape::resetPositon(const sf::Vector2f& pos)
{
	p_convexShape.setPosition(pos);
}

void PolyParticleShape::drawTo(sf::RenderWindow* window)
{
	//only render if is alive
	if (m_isVisible && window != nullptr) {
		window->draw(p_convexShape);
	}
}

void PolyParticleShape::rotate(float degrees) {

	p_convexShape.setRotation(sf::degrees(degrees));
}

void PolyParticleShape::scale(const sf::Vector2f& scale) {

	p_convexShape.setScale(scale);
}

void PolyParticleShape::generatePolygon(int nPoints, float radius)
{
	p_convexShape.setPointCount(nPoints);
	float angle, randomRadius;
	for (int i = 0; i < nPoints; i++) {
		angle = 2 * 3.14f * i / float(nPoints);
		randomRadius = MathModule::getRandom(0.5f * std::fabs(radius), std::fabs(radius));
		p_convexShape.setPoint(i, sf::Vector2f(randomRadius * cos(angle), randomRadius * sin(angle)));
	}

	angle = MathModule::getRandom(0, 90);
	p_convexShape.setRotation(sf::degrees(angle));
}

void PolyParticleShape::updatePhysics(float deltaTime) {

	if (p_isAlive) {
		p_timeAlive += deltaTime;

		//euler integration
		if (p_timeAlive >= p_timeOfBirth) {
			m_isVisible = true;
			p_state.velocity += deltaTime * p_state.acceleration;
			p_state.position += deltaTime * p_state.velocity;

			//birth sound, played when it is born:
			if (!m_birthSoundPlayed && p_birthSound != nullptr && p_birthSoundActive) {
				m_birthSoundPlayed = true;
				p_birthSound->play();
			}
		}

		if (p_deathCondition != nullptr && p_deathCondition(p_deathConditionArgsMap)) {
			death();
		}

		p_convexShape.setPosition(p_state.position);
	}
}

void PolyParticleShape::setBirthState(const State& state, float timeOfBirth)
{
	p_state = state;
	p_timeOfBirth = timeOfBirth;
	p_resetState = state;
}

void PolyParticleShape::setResetState(const State& state) {
	p_resetState = state;
}

void PolyParticleShape::setRandomBirthStateParams(const sf::Vector2f& subWindowArea) {
	m_birthParams.position = subWindowArea;
}

void PolyParticleShape::setupRandomBirthState()
{
	State state;
	state.position = { 0, MathModule::getRandom(0.2f * m_birthParams.position.y , 0.8f * m_birthParams.position.y) };//x axis
	state.velocity = { MathModule::getRandom(250,300), 0 };//y axis
	state.acceleration = { -MathModule::getRandom(80,150), 0 }; //y axis
	p_state = state;
	p_timeOfBirth = MathModule::getRandom(0, 2);

	p_resetState = state;
}

void PolyParticleShape::resetToBirthState() {
	p_state = p_resetState;
}

void PolyParticleShape::birth()
{
	p_timeAlive = 0;//reset lifetime
	m_birthSoundPlayed = false;
	p_isAlive = true;//last thing
}

void PolyParticleShape::death() {
	p_isAlive = false;//first thing
	m_isVisible = false;

	//death sound:
	if (p_deathSound != nullptr && p_deathSoundActive) {
		p_deathSound->play();
	}
}