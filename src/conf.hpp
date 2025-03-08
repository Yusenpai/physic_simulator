#pragma once

#include <SFML/Graphics.hpp>

namespace conf
{ 
	/* Window and Canvas constant */
	const sf::Vector2u window_size = {1600, 900};
	const sf::Vector2f window_size_f = static_cast<sf::Vector2f>(window_size);
	const sf::Vector2u canvas_size = {1600, 900};
	const sf::Vector2f canvas_size_f = static_cast<sf::Vector2f>(canvas_size);
	const sf::Vector2f canvas_position_f = (0.5f * (window_size_f - canvas_size_f));

	/* Physic constant */
	const uint32_t max_frame_rate = 60;
	const float dt = 1.0f / static_cast<float>(max_frame_rate);
	const float drag_coff = 0.000001f;
	const float center_force_coff = 1.5f;
	const sf::Vector2f gravity_acc = {0.0f, -1000.0f};
	const float collision_elastic_coff = 0.9f;
	const float wall_collision_elastic_coff = 0.9f;

	/* Ball constant */
	const float ball_radius = 10.0f;
	const float ball_mass = 1.0f;
	const uint32_t ball_count = 1500;
	const uint32_t ball_edge_count = 10;

	/* Grid constant */
	const float grid_spacing = 2.0f * ball_radius;
	static const sf::Vector2f grid_size_f = (1.0f / grid_spacing) * canvas_size_f;
	const sf::Vector2u grid_size = {static_cast<uint32_t>(std::round(grid_size_f.x)), static_cast<uint32_t>(std::round(grid_size_f.y))};

	const std::vector<sf::Color> catppuccin_mocha = {
		sf::Color(244, 219, 214), // Rosewater
		sf::Color(240, 198, 198), // Flamingo
		sf::Color(245, 189, 230), // Pink
		sf::Color(198, 160, 246), // Mauve
		sf::Color(138, 173, 244), // Blue
		sf::Color(166, 218, 149), // Green
		sf::Color(238, 212, 159), // Yellow
		sf::Color(245, 169, 127), // Peach
		sf::Color(237, 135, 150), // Maroon
		sf::Color(183, 189, 248)  // Lavender
	};
} // namespace conf
