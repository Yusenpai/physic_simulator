#include "rendering.hpp"

static inline uint32_t circleIndex(uint32_t j, uint32_t edge_count){
	return 3 * edge_count * j;
}

static sf::Vector2f convertPosition(sf::Vector2f point)
{
	sf::Vector2f converted_point;

	converted_point.x = conf::canvas_position_f.x + point.x;
	converted_point.y = conf::canvas_position_f.y + conf::canvas_size_f.y - point.y;

	return converted_point;
}

void drawCanvas(sf::RenderWindow &window)
{
	sf::RectangleShape canvas{conf::canvas_size_f};
	canvas.setPosition(conf::canvas_position_f);
	canvas.setFillColor(sf::Color(36, 40, 59));
	window.draw(canvas);
}

void drawBall(sf::RenderWindow &window, Ball &ball)
{
	// Simple drawing function using shape
	sf::CircleShape circle{ball.radius};
	circle.setPosition(convertPosition(ball.position));
	circle.setOrigin(sf::Vector2f{ball.radius, ball.radius});
	circle.setFillColor(ball.color);
	window.draw(circle);
}

void drawBallFast(sf::RenderWindow &window, sf::VertexArray &circles_array, std::vector<Ball> &balls)
{
	// Use Vertex Array instead.
	const uint32_t edge_count = conf::ball_edge_count;
	const float angle = 2.0f * M_PI / edge_count;
	for (uint32_t j = 0; j < balls.size(); j++)
	{
		auto ball = balls[j];
		for (uint32_t i = 0; i < edge_count; i++)
		{
			circles_array[circleIndex(j, edge_count) + 3 * i].position = convertPosition(ball.position);
			circles_array[circleIndex(j, edge_count) + 3 * i + 1].position = convertPosition(ball.position + ball.radius * sf::Vector2f{cosf(i * angle), sinf(i * angle)});
			circles_array[circleIndex(j, edge_count) + 3 * i + 2].position = convertPosition(ball.position + ball.radius * sf::Vector2f{cosf((i + 1) * angle), sinf((i + 1) * angle)});

			circles_array[circleIndex(j, edge_count) + 3 * i].color = ball.color;
			circles_array[circleIndex(j, edge_count) + 3 * i + 1].color = ball.color;
			circles_array[circleIndex(j, edge_count) + 3 * i + 2].color = ball.color;
		}
	}

	window.draw(circles_array);
}