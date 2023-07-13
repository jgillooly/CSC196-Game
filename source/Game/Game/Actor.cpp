#include "Actor.h"

void Actor::Draw(antares::Renderer& renderer) {
	m_model.Draw(renderer, m_transform);
}
