#pragma once
#include "Framework/Actor.h"
class Enemy : public antares::Actor {
public:
	Enemy(float speed, float turnRate, const antares::Transform& transform, const antares::Model& model) :
		Actor{ transform, model },
		m_speed{ speed }, m_turnRate{ turnRate } {
		m_firetime = 2.0f;
		m_firetimer = m_firetime;
	}
	void Update(float dt) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	
	float m_firetime = 0;
	float m_firetimer = 0;
};