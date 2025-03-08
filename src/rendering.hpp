#pragma once

#include <SFML/Graphics.hpp>
#include "conf.hpp"
#include "ball.hpp"
#include "math.h"

/// @brief Draw a canvas to run simulation in.
/// @param window Reference to RenderWindow object.
void drawCanvas(sf::RenderWindow &window);

/// @brief Draw a ball to window. Use sf::CircleShape to draw using a lot of costly window.draw() function.
/// @param window Reference to RenderWindow object.
/// @param ball Reference to Ball object.
void drawBall(sf::RenderWindow &window, Ball &ball);

/// @brief Draw a bunch of ball at once, hence reduce overhead. Use sf::VertexArray that contained every ball Vertex to draw.
/// @param window Reference to RenderWindow object.
/// @param circles_array Reference to Ball Vertex Array object.
/// @param balls Reference to Ball object.
void drawBallFast(sf::RenderWindow &window, sf::VertexArray &circles_array, std::vector<Ball> &balls);