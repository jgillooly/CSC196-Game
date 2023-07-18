#include "Actor.h"
namespace antares {
void Actor::Draw(antares::Renderer& renderer) {
	m_model.Draw(renderer, m_transform);
}}
