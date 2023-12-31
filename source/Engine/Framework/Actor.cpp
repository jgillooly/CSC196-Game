#include "Actor.h"
namespace antares {
	void Actor::Update(float dt) {
		if (m_lifespan != -1.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}
	}
	void Actor::Draw(antares::Renderer& renderer) {
	m_model->Draw(renderer, m_transform);
}}
