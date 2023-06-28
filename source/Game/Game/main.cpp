#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"

using namespace std;

int main() {
	cout << antares::getFilePath() << endl;
	antares::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << antares::random(5, 10) << endl;
	}
}