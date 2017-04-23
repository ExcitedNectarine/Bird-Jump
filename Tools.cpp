#include "Tools.h"

float randomFloat(const float from, const float to)
{
	unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	static std::default_random_engine engine(seed);
	std::uniform_real_distribution<float> dist(from, to);
	return dist(engine);
}