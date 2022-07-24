/*****************************************************************
 * \file	ParticleInterface.cpp
 * \brief	Functions and methods for class ParticleInterface, to be used with ParticleInterface.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "ParticleInterface.hpp"
#include "CustomSound.hpp"

ParticleInterface::ParticleInterface() :
	p_isAlive(false),
	p_birthSound(nullptr),
	p_birthSoundActive(false),
	p_deathSound(nullptr),
	p_deathSoundActive(false),
	p_deathCondition(nullptr)
{
}

void ParticleInterface::setDeathCondition(bool (*callback)(std::map<std::string, void*>), const std::map<std::string, void*>& argsMap) {
	p_deathCondition = callback;
	p_deathConditionArgsMap = argsMap;
}

bool ParticleInterface::isAlive() const {
	return p_isAlive;
}

void ParticleInterface::setBirthSound(const std::string& path, bool activate) {
	p_birthSound.reset(new CustomSound(path));
	if (activate) {
		enableBirthSound(activate);
	}
}

void ParticleInterface::enableBirthSound(bool enable) {
	p_birthSoundActive = enable;
}

void ParticleInterface::setDeathSound(const std::string& path, bool activate) {
	p_deathSound.reset(new CustomSound(path));
	if (activate) {
		enableDeathSound(activate);
	}
}

void ParticleInterface::enableDeathSound(bool enable) {
	p_deathSoundActive = enable;
}

ParticleInterface::State ParticleInterface::getState() const
{
	return p_state;
}
