#include <SFML/Graphics.hpp>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;


sf::Vector2f lerp(sf::Vector2f currentPos, sf::Vector2f finalPos, float value)
{
	sf::Vector2f pos;
	pos.x = (1 - value) * (currentPos.x) + value * (finalPos.x);
	pos.y = (1 - value) * (currentPos.y) + value * (finalPos.y);
	return pos;
}

int main()
{
	srand((unsigned int)time(NULL));

	// Create window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Lerp", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	// Paths for mouse and interpolation
	sf::VertexArray interpolatedPath(sf::LineStrip, 0);
	sf::VertexArray mousePath(sf::LinesStrip, 0);

	// Create circle as head of interpolated path
	sf::CircleShape circle(4.0f);
	circle.setOrigin(circle.getLocalBounds().width / 2.0f, circle.getLocalBounds().width / 2.0f);
	circle.setPosition((sf::Vector2f)sf::Mouse::getPosition(window));

	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			// Closed event
			if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			// Clear paths when right clicked
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right)
			{
				interpolatedPath.clear();
				mousePath.clear();
			}
		}

		// Set position of circle to head of interpolated path
		circle.setPosition(lerp(circle.getPosition(), (sf::Vector2f)sf::Mouse::getPosition(window), 0.1f));

		// Add vertex to paths
		interpolatedPath.append(sf::Vertex(circle.getPosition()));
		mousePath.append(sf::Vertex((sf::Vector2f)sf::Mouse::getPosition(window)));

		// Set color of last vertex
		interpolatedPath[interpolatedPath.getVertexCount() - 1].color = sf::Color::Green;
		mousePath[mousePath.getVertexCount() - 1].color = sf::Color::Red;

		// Clear, Draw, Display
		window.clear();
		window.draw(interpolatedPath);
		window.draw(mousePath);
		window.draw(circle);
		window.display();
	}

	return 0;
}