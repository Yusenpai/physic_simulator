#include "ball.hpp"

extern uint32_t g_collision_count;
std::vector<Ball> createBallArray(uint32_t ball_count)
{
	// Random generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	// Create Balls
	std::vector<Ball> ball_array;
	ball_array.reserve(ball_count);

	for (uint32_t i = ball_count; i--;)
	{
		const uint32_t color_index = (std::floorl(dist(gen) * conf::catppuccin_mocha.size()));
		Ball ball = {
			// ball.radius = dist(gen) * (20.0f - 5.0f) + 5.0f;
			.velocity.x = dist(gen) * 200.0f - 100.f,
			.velocity.y = dist(gen) * 200.0f - 100.f,
			.position.x = ball.radius + dist(gen) * (conf::canvas_size_f.x - 2.0f * ball.radius),
			.position.y = ball.radius + dist(gen) * (conf::canvas_size_f.y - 2.0f * ball.radius),
			.color = conf::catppuccin_mocha[color_index],
			.index = i};
		ball_array.emplace_back(ball);
	}

	return ball_array;
}

const sf::Vector2f applyDrag(Ball &ball, const float coff)
{
	const sf::Vector2f v = ball.velocity;
	const float m = ball.mass;
	const float r = ball.radius;
	const float speed = std::sqrt(v.x * v.x + v.y * v.y);
	const float surface_area = M_PI * r * r;
	auto a = -(coff / m) * speed * surface_area * v;
	return a;
}

const sf::Vector2f applyCenterForce(Ball &ball, const float coff)
{
	const sf::Vector2f r = ball.position;
	const float m = ball.mass;
	auto a = (coff / m) * (0.5f * conf::canvas_size_f - r);
	return a;
}

const sf::Vector2f applyGravity(Ball &ball, sf::Vector2f gravity)
{
	return gravity;
}

void updateBallPosition(Ball &ball, sf::Vector2f a_n, float dt)
{
	// Update ball velocity and position. Velocity Verlet method
	sf::Vector2f &r = ball.position;
	sf::Vector2f &v = ball.velocity;
	sf::Vector2f &a = ball.acceleration;

	r = (r + v * dt + 0.5f * a * dt * dt); 
	v = (v + 0.5f * (a + a_n) * dt);
	a = a_n;
}

void wallCollisionResolve(Ball &ball, const float elastic)
{
	sf::Vector2f &r = ball.position;
	sf::Vector2f &v = ball.velocity;
	const float R = ball.radius;

	if (r.x <= R)
	{
		g_collision_count++;
		r.x = R;
		v.x = -elastic * v.x;
	}
	if (r.y <= R)
	{
		g_collision_count++;
		r.y = R;
		v.y = -elastic * v.y;
	}
	if ((r.x + R) > conf::canvas_size_f.x)
	{
		g_collision_count++;
		r.x = conf::canvas_size_f.x - R;
		v.x = -elastic * v.x;
	}

	if ((r.y + R) > conf::canvas_size_f.y)
	{
		g_collision_count++;
		r.y = conf::canvas_size_f.y - R;
		v.y = -elastic * v.y;
	}
}

void ballCollisionResolve(Ball &ball1, Ball &ball2, const float elastic)
{
	sf::Vector2f &r1 = ball1.position;
	sf::Vector2f &r2 = ball2.position;
	sf::Vector2f &v1 = ball1.velocity;
	sf::Vector2f &v2 = ball2.velocity;

	const float m1 = ball1.mass;
	const float m2 = ball2.mass;
	sf::Vector2f dir = r2 - r1;
	float distance = std::sqrtf((dir.x * dir.x + dir.y * dir.y));

	// Check if collision happened
	if (distance > (ball1.radius + ball2.radius))
		return;
	else
	{
		g_collision_count++;
		if (distance < (0.01f * (ball1.radius + ball2.radius)))
			distance = 0.01f * (ball1.radius + ball2.radius);
		dir *= (1 / distance);

		// Correct ball position
		const float cor = (ball1.radius + ball2.radius - distance) / 2.0f;
		r1 -= cor * dir;
		r2 += cor * dir;

		// Find magnitude of position vector along dir vector
		float v1_dir = v1.x * dir.x + v1.y * dir.y;
		float v2_dir = v2.x * dir.x + v2.y * dir.y;

		// Calculate new magnitude of position vector along dir vector
		float v1_dir_new = (m1 * v1_dir + m2 * v2_dir - m2 * (v1_dir - v2_dir) * elastic) / (m1 + m2);
		float v2_dir_new = (m1 * v1_dir + m2 * v2_dir - m1 * (v2_dir - v1_dir) * elastic) / (m1 + m2);

		// Combined with position vector
		v1 += (v1_dir_new - v1_dir) * dir;
		v2 += (v2_dir_new - v2_dir) * dir;
	}
}