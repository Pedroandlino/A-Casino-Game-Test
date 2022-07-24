/*****************************************************************
 * \file	MathModule.cpp
 * \brief	Functions and methods for class MathModule, to be used with MathModule.hpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#include "MathModule.hpp"
#include <chrono>
#include <cstdlib>

const long long MathModule::m_ramdomizationSeed = MathModule::generateSeed();

long long MathModule::generateSeed() {
	//use time to generate random seed:
	auto timeNow = std::chrono::steady_clock::now();
	long long timeNowValue =
		std::chrono::duration_cast<std::chrono::microseconds>(timeNow.time_since_epoch()).count();
	std::srand((unsigned int)(timeNowValue));

	return timeNowValue;
}

float MathModule::getRandom(float lowestInterval, float highestInterval) {

	int random = std::rand() / ((RAND_MAX) / 100); //value [0 100]

	return (lowestInterval + 0.01f * random * (highestInterval - lowestInterval));
}