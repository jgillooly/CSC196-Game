#pragma once
#include <random>

namespace antares {
	void seedRandom(unsigned int seed) { srand(seed); }
	int random() { return rand(); }
	int random(unsigned int max) { return random() % max; }
	int random(unsigned int min, unsigned int max) { return min + random(max - min + 1); }
	int randomex(unsigned int min, unsigned int max) { return min + random(max - min); }

	float randomf() { return (float)random() / RAND_MAX; }
	float randomf(float max) { return randomf() + random(max); }
	float randomf(float min, float max) { return randomf() + randomex(min, max); }
}