/*****************************************************************
 * \file	MathModule.hpp
 * \brief	Header is for class MathModule, to be used with MathModule.cpp
 *
 * \author	Pedro Lino
 * \date	July 2022
******************************************************************/

#pragma once

#include <math.h>

/**
 * @brief MathModule static class, works as a namespace,
 * main utility is to generate random float numbers from an interval
 * also, including this class will include math.h, the idea  of this class is to be expanded
 * for the use of more utility math functions.
 */
class MathModule {
public:

	/**
	 * @brief Static method which returns a random number within an interval of values
	 * @param lowestInterval The lower interval of the random value to be generated.
	 * @param highestInterval The higher interval of the random value to be generated.
	 * @return A random value within the interval.
	 */
	static float getRandom(float lowestInterval, float highestInterval);

private:

	/** @brief Holds the seed value of the random generator */
	static const long long m_ramdomizationSeed;

	/**
	 * @brief Static method which returns a seed based on the current time
	 * to be used on the random number generator.
	 * @return A seed based on the current time.
	 */
	static long long generateSeed();
};