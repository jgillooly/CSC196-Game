#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"

namespace antares {
class Actor {
public:
	Actor() = default;
	Actor(const antares::Transform& transform, const antares::Model& model) : m_transform{transform}, m_model {model} {}

	virtual void Update(float dt);
	virtual void Draw(antares::Renderer& renderer);

	class Scene* m_scene = nullptr;
	friend class Scene;

	antares::Transform m_transform;
protected:
	antares::Model m_model;

	bool m_destroyed = false;
	float m_lifespan = -1.0f;
};
}