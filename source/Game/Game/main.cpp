#include <iostream>
#include "../../Engine/Core/Random.h"

using namespace std;

int main() {
	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << kiko::random(5, 10) << endl;
	}
}