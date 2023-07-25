#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Core/Core.h"
#include "Audio/AudioSystem.h"
#include "../../Input/InputSystem.h"
#include <memory>
#include "Core/Transform.h"
#include "Renderer/ModelManager.h"
#include "Framework/Scene.h"

bool SpaceGame::Initialize() {	
	// create font / text objects
	m_font = std::make_shared<antares::Font>("Quattrocento.ttf", 36);
	m_scoreText = std::make_unique<antares::Text>(m_font);
	m_scoreText->Create(antares::g_renderer, "SCORE: 0000", antares::Color{ 1, 1, 1, 1 });
	
	m_titleText = std::make_unique<antares::Text>(m_font);
	m_titleText->Create(antares::g_renderer, "Asteroids", antares::Color{ 1, 1, 1, 1 });

	antares::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	antares::g_audioSystem.AddAudio("laser", "LaserShoot.wav");

	m_scene = std::make_unique<antares::Scene>();
	m_state = SpaceGame::Title;
	

	return true;
}

void SpaceGame::Shutdown() {
}

void SpaceGame::Uptdate(float dt) {
	switch (m_state) {
	case SpaceGame::Title:
		if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::StartLevel:
		{ antares::Transform transform{ { 400, 300 }, 0, 5 };
		float speed = 100;
		constexpr float turnRate = antares::Degrees2Radians(180.0f);
		std::unique_ptr<Player> player = std::make_unique<Player>(400, antares::Pi, transform, antares::g_manager.Get("Diamond.txt"));

		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));
		m_state = eState::Game;
		break; }
	case SpaceGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;
			float rotat = antares::randomf(antares::TwoPi);
			antares::Transform t1{ {400, 300}, rotat, 2};
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(antares::random(150, 250), 200, t1, antares::g_manager.Get("Diamond.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case SpaceGame::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;
		break;
	case SpaceGame::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(antares::g_renderer, "Score:" + std::to_string(m_score), antares::Color{ 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(antares::Renderer& renderer) {
	if (m_state == eState::Title) m_titleText->Draw(renderer, 400, 300);

	m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
}
