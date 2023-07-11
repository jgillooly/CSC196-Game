#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"

using namespace std;

class Star {
public:
	Star(const antares::Vector2& position, const antares::Vector2& velocity) : m_position{ position }, m_velocity{ velocity } {};
	void Update() {
		m_position += m_velocity;
	}
public:
	antares::Vector2 m_position;
	antares::Vector2 m_velocity;
};

int main(int argc, char* argv[]) {
	antares::seedRandom(time(NULL));

	vector<Star> points;
	antares::Renderer renderer;
	renderer.CreateWindow("window", 800, 600);
	renderer.Initialize();
	cout << renderer.GetWidth() << "x" << renderer.GetHeight();

	for (int i = 0; i < 1000; i++) {
		points.push_back(Star(antares::Vector2(antares::random(renderer.GetWidth()), antares::random(renderer.GetHeight())), antares::Vector2(1,1)));
	}

	while (true) {
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
		for (auto& point : points) {
			int r = antares::random(256);
			int g = antares::random(256);
			int b = antares::random(256);
			renderer.SetColor(r, g, b, SDL_ALPHA_OPAQUE);
			point.Update();
			if (point.m_position.x > renderer.GetWidth()) point.m_position.x = 0;
			if (point.m_position.y > renderer.GetHeight()) point.m_position.y = 0;

			renderer.DrawPoint(point.m_position.x, point.m_position.y);
		}
		renderer.EndFrame();
	}

	return 0;
}