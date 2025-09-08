#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace sf;

int main() {

	//Create Window
	RenderWindow window(VideoMode({ 1200 , 800 }), "SpawnBalls");

	//Vector for Circles
	vector <CircleShape> circles;

	//Clock
	Clock clock;
	Clock deltaclock;

	//Variables
	bool ispressed = false;
	float elapsedTime = 0.f;
	int Index = -1;
	float gravity = 300.f;
	Vector2f velocity(0.f, 0.f);

	//Main Infinity Loop
	while (window.isOpen()) {
		
		//Delta Time
		float dt = deltaclock.restart().asSeconds();

		//To Handle Events
		while (optional event = window.pollEvent()) {

			//To close window
			if (event->is<Event::Closed>()) {
				window.close();
			}

			//To prevent streching 
			if (event->is<Event::Resized>()) {
				View view(FloatRect({ 0.f , 0.f }, Vector2f(window.getSize())));
				window.setView(view);
			}

			//Mouse Input
			if (auto* mouse = event->getIf<Event::MouseButtonPressed>()) {
				if (mouse->button == Mouse::Button::Left) {
					clock.restart();
					ispressed = true;
					Index += 1;

					CircleShape circle(0.f);         //Start with 0 radius
					circle.setOrigin({ 0.f, 0.f });
					circle.setPosition(Vector2f(mouse->position));  //Set Circle Position to Mouse Position
					circles.push_back(circle);
				}
			}
			if (auto* mouse = event->getIf<Event::MouseButtonReleased>()) {
				if (mouse->button == Mouse::Button::Left) {
					ispressed = false;
				}
			}
		}
		
		//Increase Size of Circles in Real Time
		if (ispressed && Index >= 0) {
			float elapsedTime = clock.getElapsedTime().asSeconds();     //Get Elapsed Time to Increase Radius
			float radius = elapsedTime * 50;          
			circles[Index].setRadius(radius);
			circles[Index].setOrigin({ radius , radius });
		}

		//Set Window Color
		window.clear(Color::Black);
		
		//Display Circles
		for (auto& c : circles) {
			
			window.draw(c);
		}

		//Display Window
		window.display();

	}
}
