#include <iostream>
#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <chrono>
#include "Core/Time.h"
//#include "Renderer/Renderer.h"

using namespace std;

void func() {
	int* p = new int[1000000];
}





int main() {
	antares::g_memoryTracker.displayInfo();
	int* p = new int;
	antares::g_memoryTracker.displayInfo();
	delete p;
	antares::g_memoryTracker.displayInfo();

	antares::Time timer;
	for (int i = 0; i < 1000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << timer.GetElapsedMilliseconds() << endl;

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