#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "conf.hpp"

/// @brief A simple Ball object that simulate a real ball.
struct Ball
{
	float radius = conf::ball_radius;
	float mass = conf::ball_mass;
	uint32_t index = 0;
	sf::Vector2f position = {0.0f, 0.0f};
	sf::Vector2f velocity = {0.0f, 0.0f};
	sf::Vector2f acceleration = conf::gravity_acc;
	sf::Color color = conf::catppuccin_mocha[0];
};

/// @brief Create and std::array of Ball, with random color, velocity, position.
/// @param ball_count Number of ball create. Default value: conf::ball_count.
/// @return Reference to array of created Ball.
std::vector<Ball> createBallArray(uint32_t ball_count = conf::ball_count);

/// @brief Calculate drag caused by air. This force depends on ball velocity.
/// @param ball Reference to ball object.
/// @param coff Drag coefficent. Higher mean more drag.
/// @return sf::Vector2f of accleration on that ball.
const sf::Vector2f applyDrag(Ball &ball, const float coff = conf::drag_coff);

/// @brief Calculate center force that pull ball to the center of the screen. This force depends on the distance from the center to the ball.
/// @param ball Reference to ball object.
/// @param coff Center force propotional constant. Higher means stronger force.
/// @return sf::Vector2f of accleration on that ball.
const sf::Vector2f applyCenterForce(Ball &ball, const float coff = conf::center_force_coff);

/// @brief Calculate gravity that act on the ball. This force is ball's mass times g.
/// @param ball Reference to ball object.
/// @param gravity Gravity vector that apply on the ball. Default is conf::gravity_acc.
/// @return sf::Vector2f of accleration on that ball.
const sf::Vector2f applyGravity(Ball &ball, const sf::Vector2f gravity = conf::gravity_acc);

/// @brief Update the position, velocity of the ball based on its previous position, velocity and acceleration. Based on Verlet velocity intergration for high accurate result.
/// @param ball Reference to ball object.
/// @param a_n New acceleration apply on ball.
/// @param dt Time step. Smaller mean higher accuracy.
void updateBallPosition(Ball &ball, sf::Vector2f a_n, float dt = conf::dt);

/// @brief Resolve collision between ball and wall.
/// @param ball Reference to ball object.
/// @param elastic Elastic coefficient. e = 1 means hard collision. 0 < e < 1 mean soft collision.
void wallCollisionResolve(Ball &ball, const float elastic = conf::collision_elastic_coff);

/// @brief Resolve collision between ball and ball.
/// @param ball1 Reference to first ball object.
/// @param ball2 Reference to second ball object.
/// @param elastic Elastic coefficient. e = 1 means hard collision. 0 < e < 1 mean soft collision.
void ballCollisionResolve(Ball &ball1, Ball &ball2, const float elastic = conf::wall_collision_elastic_coff);