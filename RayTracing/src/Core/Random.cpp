#include "Core/Random.h"

namespace RayTracing
{

	std::mt19937 Random::s_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_Disribution;

}