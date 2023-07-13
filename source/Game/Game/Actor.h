#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"

class Actor {
public:
	Actor() = default;
	Actor(const antares::Transform& transform, const antares::Model& model) : m_transform{transform}, m_model {model} {}

	virtual void Update(float dt) = 0;
	virtual void Draw(antares::Renderer& renderer);
protected:
	antares::Transform m_transform;
	antares::Model m_model;
};