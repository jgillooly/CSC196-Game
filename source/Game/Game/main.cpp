#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"

using namespace std;

void func() {
	int* p = new int[1000000];
}

void funcs() {
	int i[100000];
	funcs();
}




int main() {
	for (int i = 0; i < 10; i++) {
		int* p = new int;
		delete p;
	}

	cout << antares::getFilePath() << endl;
	antares::setFilePath("Assets");
	cout << antares::getFilePath() << endl;
	size_t size;
	antares::getFileSize("Game.txt", size);
	cout << size << endl << endl;
	std::string data;
	antares::readFile("Game.txt", data);
	cout << data << endl << endl;
	antares::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++) {
		cout << antares::random(5, 10) << endl;
	}
}