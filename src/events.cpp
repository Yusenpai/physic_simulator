#include "events.hpp"

void processEvents(sf::Window &window)
{
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;

			case sf::Keyboard::R:
				g_balls = createBallArray(conf::ball_count);
				break;

			case sf::Keyboard::F:
				g_is_applying_force = !g_is_applying_force;
				break;
			default:
				break;
			}
		}
	}
}
