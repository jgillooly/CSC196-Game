#include <iostream>
#include "Core/Core.h"
#include <chrono>
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "../../Input/InputSystem.h"
#include <thread>
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"

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
	antares::g_renderer.CreateWindow("window", 800, 600);
	antares::g_renderer.Initialize();
	cout << antares::g_renderer.GetWidth() << "x" << antares::g_renderer.GetHeight();

	antares::g_inputSystem.Initialize();

	antares::g_audioSystem.Initialize();
	antares::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	antares::g_audioSystem.AddAudio("laser", "LaserShoot.wav");

	std::vector<antares::vec2> points{ {-10, 5}, { 10, 5 }, { 0, -5 }, { -10, 5 } };
	antares::Model model;
	model.Load("Diamond.txt");

	antares::vec2 v{5, 5};
	v.Normalize();

	for (int i = 0; i < 1000; i++) {
		stars.push_back(Star(antares::Vector2(antares::random(antares::g_renderer.GetWidth()), antares::random(antares::g_renderer.GetHeight())),
			antares::Vector2(100,100)));
	}
	antares::Transform transform{{ 400, 300 }, 0, 1};
	float speed = 100;
	constexpr float turnRate = antares::Degrees2Radians(180.0f);
	Player player{200, antares::Pi, {{400,300}, 0, 5}, model };
	float rotat = antares::randomf(antares::TwoPi);
	std::vector<Enemy> enemies;
	for (int i = 0; i < 200; i++) {
		enemies.push_back({ 200, 200, {{400,300}, rotat, 2}, model });
	}

	bool quit = false;

	while (!quit) {
		antares::g_audioSystem.Update();
		antares::g_time.Tick();
		antares::g_inputSystem.Update();
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		if(antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			antares::g_audioSystem.PlayOneShot("laser");
		}

		if (antares::g_inputSystem.GetMouseButtonDown(0)) {
			cout << "Mouse Pressed" << endl;
			cout << "Mouse Position: (" << antares::g_inputSystem.GetMousePosition().x << "," << antares::g_inputSystem.GetMousePosition().y << ")" << endl;
		}

		antares::g_renderer.SetColor(0, 0, 0, 0);
		antares::g_renderer.BeginFrame();
		//renderer.SetColor(255, 255, 255, SDL_ALPHA_OPAQUE);
		for (auto& point : stars) {
			int r = antares::random(256);
			int g = antares::random(256);
			int b = antares::random(256);
			antares::g_renderer.SetColor(r, g, b, SDL_ALPHA_OPAQUE);
			point.Update();
			if (point.m_position.x > antares::g_renderer.GetWidth()) point.m_position.x = 0;
			if (point.m_position.y > antares::g_renderer.GetHeight()) point.m_position.y = 0;

			antares::g_renderer.DrawPoint(point.m_position.x, point.m_position.y);
		}
		player.Update(antares::g_time.getDeltaTime());
		player.Draw(antares::g_renderer);
		for (auto enemy : enemies) {
			enemy.Update(antares::g_time.getDeltaTime());
			enemy.Draw(antares::g_renderer);
		}
		//enemy.Update(antares::g_time.getDeltaTime());
		//enemy.Draw(antares::g_renderer);
		//model.Draw(renderer, transform.position, transform.rotation, transform.scale);

		antares::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(15));
	}

	return 0;
}