#include "RenderThread.h"

void renderingThread(sf::RenderWindow &window, Vec2d &pos, int &enb){
	// activate the window's context
	window.setActive(true);
	// the rendering loop
	while (window.isOpen() && enb>0){
		// draw...
		sf::CircleShape ball(10.f);
		ball.setPosition(sf::Vector2f(pos.getX(), pos.getY()));
		ball.setFillColor(sf::Color(240, 240, 240));
		window.clear(sf::Color::Black);
		window.draw(ball);
		// end the current frame
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
