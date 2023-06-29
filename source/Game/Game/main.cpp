#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <chrono>

using namespace std;

void func() {
	int* p = new int[1000000];
}

void funcs() {
	int i[1000];
	funcs();
}




int main() {
	antares::g_memoryTracker.displayInfo();
	int* p = new int;
	antares::g_memoryTracker.displayInfo();
	delete p;
	antares::g_memoryTracker.displayInfo();

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	//for (int i = 0; i < 10; i++) {
	//}

	//cout << antares::getFilePath() << endl;
	//antares::setFilePath("Assets");
	//cout << antares::getFilePath() << endl;
	//size_t size;
	//antares::getFileSize("Game.txt", size);
	//cout << size << endl << endl;
	//std::string data;
	//antares::readFile("Game.txt", data);
	//cout << data << endl << endl;
	//antares::seedRandom((unsigned int)time(nullptr));
	//for (int i = 0; i < 10; i++) {
	//	cout << antares::random(5, 10) << endl;
	//}

}