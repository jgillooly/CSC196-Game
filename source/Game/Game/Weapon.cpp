#include "Weapon.h"

void Weapon::Update(float dt) {
	Actor::Update(dt);
	antares::vec2 forward = antares::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * antares::g_time.getDeltaTime();

	m_destroyed = ((m_transform.position.x > antares::g_renderer.GetWidth() || m_transform.position.x < 0) || (m_transform.position.y > antares::g_renderer.GetHeight() || m_transform.position.y < 0));
}