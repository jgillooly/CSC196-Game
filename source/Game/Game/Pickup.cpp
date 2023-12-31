#include "Pickup.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"

void Pickup::Update(float dt) {
	m_life += dt;
	if (m_life >= m_lifespan) {
		m_destroyed = true;
	}
}

void Pickup::OnCollision(Actor* other) {
	if (other->m_tag == "Player") {
		m_destroyed = true;
		m_game->SetLives(m_game->GetLives() + 1);
	}
}
