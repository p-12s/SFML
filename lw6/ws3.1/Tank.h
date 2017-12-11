#pragma once
#include <SFML/Graphics.hpp>

class Tank
{
public:
	Tank(AnimatedSprite& sprite);

	// Экземпляры класса нельзя копировать
	Tank(const Tank&) = delete;
	Tank& operator=(const Tank&) = delete;

	void update(float dt);

private:
	enum class State
	{
		StandsStill
		MovesToLeft,
		MovesToRight,
		MovesToUp,
		MovesToDown
		// добавить состояния движения по диагонали
	};

	State m_state = State::StandsStill;
/*
	void updateIdleOrWalking(float dt);
	void updateJumping(float dt);
	void switchState(State state);
*/

	sf::RectangleShape m_gun;
	sf::CircleShape m_body;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
	float m_rotation;
	
/*
	AnimatedSprite& m_sprite;
	float m_jumpStartY = 0;
	AnimationUpdateFn m_updateAnimation;
*/

};