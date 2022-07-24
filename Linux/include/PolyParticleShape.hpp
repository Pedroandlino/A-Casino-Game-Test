/*****************************************************************
 * \file	PolyParticleShape.hpp
 * \brief	Header is for class PolyParticleShape, to be used with PolyParticleShape.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include "WindowInterface.hpp"
#include "ParticleInterface.hpp"
#include <string>

#include <SFML/Graphics.hpp>

/**
 * @brief PolyParticleShape class is particle shape, composed from n vertices
 * it was initially thougth out to generate random particles with random states
 * as well as randomize its texture color.
 */

class PolyParticleShape : public WindowInterface, public ParticleInterface
{
	//TODO: create BaseShape < WindowInterface, and BoxShape < BaseShape
public:

	/**
	 * @brief Structure composed by a group of birth parameters
	 */
	struct BirthParams {
		/** @brief Holds the 2d position of birth coordinates for the particle. */
		sf::Vector2f position;
	};

	/**
	 * @brief Constructor.
	 * @param pos The position of the particle.
	 * @param nPoints The number of poins of the polygon.
	 * @param radius The radius of the polygon.
	 * @param backgroundColor The base color of the polygon.
	 */
	PolyParticleShape(
		const sf::Vector2f& pos,
		int nPoints,
		float radius,
		const sf::Color& backgroundColor);

	/**
	 * @brief Constructor.
	 * @param pos The position of the particle.
	 * @param nPoints The number of poins of the polygon.
	 * @param radius The radusi of the polygon.
	 * @param path The path to the texture of the polygon.
	 */
	PolyParticleShape(
		const sf::Vector2f& pos,
		int nPoints,
		float radius,
		const std::string& path);

	/**
	 * @brief Default destructor.
	 */
	~PolyParticleShape() = default;

	/**
	 * @brief Method which sets a texture of the polygon and sets
	 * if it should become immedialty active.
	 * @param path The path the texture to be loaded for the rectangle shape.
	 * @param activate Activates the texture.
	 */
	void setTexture(const std::string& path, bool activate = true);

	/**
	 * @brief Method which enables the texture to be rendered over the shape background color.
	 * @param enable The enable flag.
	 */
	void enableTexture(bool enable);

	/**
	 * @brief Method which randomizes the particle's texture background color.
	 */
	void randomizeColor();

	/**
	 * @brief Method which resets the position of the shape to a new position.
	 * @param pos The new position coordinate.
	 */
	void resetPositon(const sf::Vector2f& pos);

	/**
	 * @brief Method which draws the rectangle shape to a specific window.
	 * @param window The window object reference.
	 */
	void drawTo(sf::RenderWindow* window) override;

	/**
	 * @brief Method which updates the internal state of the object
	 * based on deltaTime.
	 * @param deltaTime The time interval to update the differential equations.
	 */
	void updatePhysics(float deltaTime) override;

	void setRandomBirthStateParams(const sf::Vector2f& subWindowArea);

	/**
	 * @brief Method which sets the internal birth state of the object.
	 * @param state The state to be born with.
	 * @param timeOfBirth The time the objects is suposed to be born.
	 */
	void setBirthState(const State& state, float timeOfBirth = 0) override;

	/**
	 * @brief Method which sets the internal reset state of the object.
	 * @param state The state to be reset with.
	 */
	void setResetState(const State& state) override;

	/**
	 * @brief Method which sets up a random birth state, and saves it to reset state.
	 */
	void setupRandomBirthState();

	/**
	 * @brief Method which implements a resetToBirthState behaviour.
	 */
	void resetToBirthState() override;

	/**
	 * @brief Method which implements a birth behaviour.
	 */
	void birth() override;

	/**
	 * @brief Method which implements a death behaviour.
	 */
	void death() override;

	/**
	 * @brief Method which rotates the ConvexShape polygon shape.
	 * @param degrees The angle to rotate.
	 */
	void rotate(float degrees);

	/**
	 * @brief Method which scales the ConvexShape polygon shape.
	 * @param scale The scale x,y values to scales the ConvexShape.
	 */
	void scale(const sf::Vector2f& scale);

protected:

	/** @brief Holds the flag value, true if the texture is active. */
	bool p_textureActive;

	/** @brief Holds the composing ConvexShape object. */
	sf::ConvexShape p_convexShape;

	/** @brief Holds the Texture reference, if it is allocated. */
	boost::shared_ptr<sf::Texture> p_texture;

private:
	/**
	 * @brief Method which generates the internal ConvexShape/polygon object, based on inputs.
	 * this way of constructing the ConvexShape will approximate the creation of a circle
	 * @param nPoints The numebr of polygon vertices.
	 * @param radius The radius of the polygon to be reset with.
	 */
	void generatePolygon(int nPoints, float radius);

	/** @brief Holds the birth Parameters of the particle. */
	BirthParams m_birthParams;

	/** @brief Holds a flag value, true if the particle is to be rendered. */
	bool m_isVisible;

	/** @brief Holds a flag value, true if birth sound has been played. */
	bool m_birthSoundPlayed;
};