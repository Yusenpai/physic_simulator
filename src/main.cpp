#include <SFML/Graphics.hpp>
#include "engine.hpp"

// Global Variables
std::vector<Ball> g_balls;
bool g_is_applying_force = false;
uint32_t g_collision_count = 0;

struct AppContext
{
	sf::RenderWindow window;
	sf::Font font;
	sf::Text fps_text;
	sf::Text collision_count_text;
	sf::VertexArray balls_va;
	sf::Clock clock;
};

static AppContext app;

// Function Declarations
static void initialize();
static void runSimulation();
static void updatePhysics();
static void render();

int main()
{
	initialize();
	while (app.window.isOpen())
	{
		processEvents(app.window);
		runSimulation();
		render();
	}
	
	return 0;
}

// **Initialization Function**
static void initialize()
{
	auto &window = app.window;
	auto &font = app.font;
	auto &fps_text = app.fps_text;
	auto &collision_count_text = app.collision_count_text;
	auto &balls_va = app.balls_va;

	window.create({conf::window_size.x, conf::window_size.y}, "Physics Simulator", sf::Style::Default);
	window.setFramerateLimit(conf::max_frame_rate);
	window.setMouseCursorVisible(false);

	if (!font.loadFromFile("res/roboto.ttf"))
	{
		std::cerr << "Failed to load font!" << std::endl;
		exit(-1);
	}

	// FPS Text
	fps_text.setFont(font);
	fps_text.setCharacterSize(20);
	fps_text.setFillColor(sf::Color::White);
	fps_text.setPosition(10, 10);

	// Collision Count Text
	collision_count_text.setFont(font);
	collision_count_text.setCharacterSize(20);
	collision_count_text.setFillColor(sf::Color::White);
	collision_count_text.setPosition(10, 40);

	// Create Ball Array
	g_balls = createBallArray();
	balls_va = sf::VertexArray(sf::PrimitiveType::Triangles, 3 * conf::ball_edge_count * g_balls.size());
}

// **Main Simulation Loop**
static void runSimulation()
{
	auto &clock = app.clock;
	auto &balls_va = app.balls_va;
	auto &window = app.window;
	auto &collision_count_text = app.collision_count_text;
	auto &fps_text = app.fps_text;

	float elapsed_time = clock.restart().asSeconds();
	fps_text.setString("FPS: " + std::to_string(static_cast<int>(1.0f / elapsed_time)));
	collision_count_text.setString("Collisions: " + std::to_string(g_collision_count));

	updatePhysics();
}

// **Physics Update Function**
static void updatePhysics()
{
	float dt = conf::dt;
	const uint32_t step = 10;
	dt /= step;

	for (uint32_t time_step = step; time_step--;)
	{
		for (size_t i = 0; i < g_balls.size(); i++)
		{
			sf::Vector2f acceleration = applyDrag(g_balls[i]);

			if (g_is_applying_force)
				acceleration += applyCenterForce(g_balls[i]);
			else
				acceleration += applyGravity(g_balls[i]);

			updateBallPosition(g_balls[i], acceleration, dt);
			wallCollisionResolve(g_balls[i]);

			for (size_t j = i + 1; j < g_balls.size(); j++)
			{
				ballCollisionResolve(g_balls[i], g_balls[j]);
			}
		}
	}
}

// **Rendering Function**
static void render()
{
	auto &window = app.window;
	auto &font = app.font;
	auto &fps_text = app.fps_text;
	auto &collision_count_text = app.collision_count_text;
	auto &balls_va = app.balls_va;
	window.clear();
	drawCanvas(window);
	drawBallFast(window, balls_va, g_balls);
	window.draw(fps_text);
	window.draw(collision_count_text);
	window.display();
}