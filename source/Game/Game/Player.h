#pragma once
#include "Framework/Actor.h"
class Player : public antares::Actor {
public:
	Player(float speed, float turnRate, const antares::Transform& transform, std::shared_ptr<antares::Model> model) :
		Actor{ transform, model },
		m_speed{speed}, m_turnRate{turnRate}
	{}
	void Update(float dt) override;

	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 200;
};