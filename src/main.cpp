#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <GL/gl.h>

int main()
{
	// Time Test
	sf::Clock Clock;
	double Time = 0.0;
	const double DeltaTime = 1.0 / 20.0;

	double CurrentTime = Clock.getElapsedTime().asSeconds();
	double Accumulator = 0.0;

	sf::RenderWindow Window(sf::VideoMode(800, 600), "Window");
	Window.setVerticalSyncEnabled(true);

	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::Green);
	sf::Vector2f ShapePosition = shape.getPosition();
	sf::Vector2f PreviousShapePosition = shape.getPosition();

	bool Left = false;
	bool Right = false;
	bool Up = false;
	bool Down = false;
	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					Left = true;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					Right = true;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					Up = true;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					Down = true;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					Left = false;
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					Right = false;
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					Up = false;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					Down = false;
				}
			}
		}

		double NewTime = Clock.getElapsedTime().asSeconds();
		double FrameTime = NewTime - CurrentTime;
		CurrentTime = NewTime;

		Accumulator += FrameTime;

		int StepCount = 0;
		while (Accumulator >= DeltaTime)
		{
			StepCount++;
			Accumulator -= DeltaTime;
			Time += DeltaTime;
		}

		for (int i = 0; i < StepCount; i++)
		{
			PreviousShapePosition = ShapePosition;

			const int MovementAmount = 5;
			if (Left)
			{
				ShapePosition.x -= MovementAmount;
			}

			if (Right)
			{
				ShapePosition.x += MovementAmount;
			}

			if (Up)
			{
				ShapePosition.y -= MovementAmount;
			}

			if (Down)
			{
				ShapePosition.y += MovementAmount;
			}
		}

		sf::Vector2f Interpolated = sf::Vector2f(0,0);
		const double alpha = Accumulator / DeltaTime;
		Interpolated.x = ShapePosition.x * alpha + PreviousShapePosition.x * ( 1.0 - alpha );
		Interpolated.y = ShapePosition.y * alpha + PreviousShapePosition.y * ( 1.0 - alpha );
		shape.setPosition(Interpolated);

		Window.clear();
		Window.draw(shape);
		Window.display();
		glFinish(); // help prevent skips in windowed mode

		std::stringstream ss;
		ss << 1.0f / FrameTime;
		Window.setTitle(ss.str());
	}

	return 0;
}
