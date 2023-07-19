#include "Player.h"
#include "../../Input/InputSystem.h"
#include "Weapon.h"
#include "Framework/Scene.h"

void Player::Update(float dt) {
	Actor::Update(dt);

	if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !antares::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) {
		antares::Transform transform2 {m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400, 0, transform2, m_model );
		m_scene->Add(std::move(weapon));
	}

	float rotate = 0;
	if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * antares::g_time.getDeltaTime();

	float thrust = 0;
	if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (antares::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * antares::g_time.getDeltaTime() * thrust;

	antares::vec2 direction;
	//m_transform.position += (direction.Rotate(m_transform.rotation) * m_speed * antares::g_time.getDeltaTime());
	m_transform.position.x = antares::Wrap(m_transform.position.x, (float)antares::g_renderer.GetWidth());
	m_transform.position.y = antares::Wrap(m_transform.position.y, (float)antares::g_renderer.GetHeight());
}
