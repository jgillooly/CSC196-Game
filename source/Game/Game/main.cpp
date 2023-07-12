#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "../../Input/InputSystem.h"
#include <thread>

using namespace std;

class Star {
public:
	Star(const antares::Vector2& position, const antares::Vector2& velocity) : m_position{ position }, m_velocity{ velocity } {};
	void Update() {
		m_position += m_velocity * antares::g_time.getDeltaTime();
	}
public:
	antares::Vector2 m_position;
	antares::Vector2 m_velocity;
};

int main(int argc, char* argv[]) {

	antares::seedRandom(time(NULL));
	antares::setFilePath("assets");
	vector<Star> stars;
	antares::Renderer renderer;
	renderer.CreateWindow("window", 800, 600);
	renderer.Initialize();
	cout << renderer.GetWidth() << "x" << renderer.GetHeight();

	antares::InputSystem inputSystem;
	inputSystem.Initialize();

	std::vector<antares::vec2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, { -10, 5 } };
	antares::Model model;
	model.Load("Diamond.txt");

	antares::vec2 v{5, 5};
	v.Normalize();



	for (int i = 0; i < 1000; i++) {
		stars.push_back(Star(antares::Vector2(antares::random(renderer.GetWidth()), antares::random(renderer.GetHeight())), 
			antares::Vector2(100,100)));
	}
	antares::Transform transform{{ 400, 300 }, 0, 1};
	float speed = 100;
	float turnRate = antares::Degrees2Radians(180.0f);

	bool quit = false;

	while (!quit) {
		antares::g_time.Tick();
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		float rotate = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnRate * antares::g_time.getDeltaTime();

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
		antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * antares::g_time.getDeltaTime() * thrust;

		antares::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		transform.position += ( direction.Rotate(transform.rotation) * speed * antares::g_time.getDeltaTime() );
		//transform.position.x = antares::Wrap(transform.position.x, renderer.GetWidth());
		//transform.position.y = antares::Wrap(transform.position.y, renderer.GetHeight());

		if (inputSystem.GetMouseButtonDown(0)) {
			cout << "Mouse Pressed" << endl;
			cout << "Mouse Position: (" << inputSystem.GetMousePosition().x << "," << inputSystem.GetMousePosition().y << ")" << endl;
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
		for (auto& point : stars) {
			int r = antares::random(256);
			int g = antares::random(256);
			int b = antares::random(256);
			renderer.SetColor(r, g, b, SDL_ALPHA_OPAQUE);
			point.Update();
			if (point.m_position.x > renderer.GetWidth()) point.m_position.x = 0;
			if (point.m_position.y > renderer.GetHeight()) point.m_position.y = 0;

			renderer.DrawPoint(point.m_position.x, point.m_position.y);
		}
		model.Draw(renderer, transform.position, transform.rotation, transform.scale);

		renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(15));
	}

	return 0;
}