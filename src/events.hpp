#pragma once
#include <SFML/Window.hpp>
#include "ball.hpp"
#include "conf.hpp"

extern std::vector<Ball> g_balls;
extern bool g_is_applying_force;
void processEvents(sf::Window &window);