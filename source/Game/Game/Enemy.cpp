#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include <memory>

void Enemy::Update(float dt) {
	Actor::Update(dt);

	Player* p = m_scene->GetActor<Player>();

	if (p) {
		antares::Vector2 direction = p->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + antares::HalfPi;

	}

	antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * antares::g_time.getDeltaTime();

	m_transform.position.x = antares::Wrap(m_transform.position.x, (float)antares::g_renderer.GetWidth());
	m_transform.position.y = antares::Wrap(m_transform.position.y, (float)antares::g_renderer.GetHeight());

	m_firetimer -= dt;
	if (m_firetimer <= 0) {
		antares::Transform transform2 {m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400, 0, transform2, m_model);
		m_scene->Add(std::move(weapon));
		m_firetimer = m_firetime;
	}
}