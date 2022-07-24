/*****************************************************************
 * \file	ParticleInterface.hpp
 * \brief	Header is for class ParticleInterface, to be used with ParticleInterface.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <string>
#include <map>

#include <SFML/System/Vector2.hpp>
#include <boost/shared_ptr.hpp>

class CustomSound;

/**
 * @brief ParticleInterface class hadles common behaviour of particles and their properties,
 * as well as forcing the implementation of common behaviours of such.
 */
class ParticleInterface
{
public:

	/**
	 * @brief Structure composed of phyical state variables
	 */
	struct State {
		/** @brief Holds the 2d position physical property. */
		sf::Vector2f position = { 0,0 };

		/** @brief Holds the 2d velocity physical property. */
		sf::Vector2f velocity = { 0,0 };

		/** @brief Holds the 2d acceleration physical property. */
		sf::Vector2f acceleration = { 0,0 };
	};

	/**
	 * @brief Default constructor.
	 */
	ParticleInterface();

	/**
	 * @brief Default destructor.
	 */
	~ParticleInterface() = default;

	/**
	 * @brief Method which forces child classes to update the internal state of the object
	 * based on deltaTime.
	 * @param deltaTime The time interval to update the differential equations.
	 */
	virtual void updatePhysics(float deltaTime) = 0;

	/**
	 * @brief Method which forces child classes to set the internal birth state of the object.
	 * @param state The state to be born with.
	 * @param timeOfBirth The time the objects is suposed to be born.
	 */
	virtual void setBirthState(const State& state, float timeOfBirth = 0) = 0;

	/**
	 * @brief Method which forces child classes to set the internal reset state of the object.
	 * @param state The state to be reset with.
	 */
	virtual void setResetState(const State& state) = 0;

	/**
	 * @brief Method which forces child classes to implement a birth behaviour.
	 */
	virtual void birth() = 0;

	/**
	 * @brief Method which forces child classes to implement a death behaviour.
	 */
	virtual void death() = 0;

	/**
	 * @brief Method which forces child classes to implement a resetToBirthState behaviour.
	 */
	virtual void resetToBirthState() = 0;

	//TODO: eventually setTrajectory()

	//TODO: eventually setBirthCallback()

	/**
	 * @brief Method which sets the death vericication callback, in is called on updatePhysics.
	 * @param callback A function pointer.
	 * @param argsMap The function's arguments map.
	 * @see updatePhysics()
	 */
	virtual void setDeathCondition(bool (*callback)(std::map<std::string, void*>), const std::map<std::string, void*>& argsMap);

	/**
	 * @brief Method which checks if the current particle is alive or dead.
	 * @return The value of true if the current parrticle is alive .
	 */
	bool isAlive() const;

	/**
	 * @brief Method which sets and loads the birth behaviour sound.
	 * @param path The path of the sound to be played.
	 * @param activate If the sound should start active.
	 */
	void setBirthSound(const std::string& path, bool activate = true);

	/**
	 * @brief Method which sets if the birth should be played.
	 * @param enable The value to enable the playing of the sound.
	 */
	void enableBirthSound(bool enable);

	/**
	 * @brief Method which sets and loads the death behaviour sound.
	 * @param path The path of the sound to be played.
	 * @param activate If the sound should start active.
	 */
	void setDeathSound(const std::string& path, bool activate = true);

	/**
	 * @brief Method which sets if the death should be played.
	 * @param enable The value to enable the playing of the sound.
	 */
	void enableDeathSound(bool enable);

	/**
	 * @brief Method which gets the current internal state of the particle.
	 * @return The current internal state of the particle.
	 */
	State getState() const;

protected:
	/** @brief Holds the current state of the particle. */
	State p_state;

	/** @brief Holds the reset state of the particle. */
	State p_resetState;

	/** @brief Holds the flag value, true if the partile is alive. */
	bool p_isAlive = false;

	/** @brief Holds the CustomSound reference for the birth sound, if it is allocated. */
	boost::shared_ptr<CustomSound> p_birthSound;

	/** @brief Holds the flag value, true if the birth sound is active. */
	bool p_birthSoundActive;

	/** @brief Holds the CustomSound reference for the death sound, if it is allocated. */
	boost::shared_ptr<CustomSound> p_deathSound;

	/** @brief Holds the flag value, true if the death sound is active. */
	bool p_deathSoundActive;

	/**
	 * @brief Holds the callback function to be called when setDeathCondition is evoked.
	 * @see setDeathCondition()
	 */
	bool (*p_deathCondition)(std::map<std::string, void*>);

	/**
	 * @brief Holds the parameters of the callback function to be called when setDeathCondition is evoked.
	 * @see setDeathCondition()
	 */
	std::map<std::string, void*> p_deathConditionArgsMap;

	/** @brief Holds the value of the time the object should be born. */
	float p_timeOfBirth;

	/** @brief Holds the value of the time the object has been 'physically' alive. */
	float p_timeAlive;
};