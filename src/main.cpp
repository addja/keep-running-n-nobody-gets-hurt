// Main 

#include "include/globals.hpp"
#include "include/cGame.hpp"
#include "include/cMenu.hpp"

int main() {
	// create window and initialize it
    sf::ContextSettings Settings;
	Settings.depthBits         = 24; // Request a 24 bits depth buffer
	Settings.stencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
	sf::Window window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT, 32), GAME_TITLE, sf::Style::Close, Settings);

    sf::Event event;
	window.setKeyRepeatEnabled(false); // not count key holding press
	sf::Clock clock;
	sf::Time elapsed;

	// create menu
	window.setActive();
	cMenu menu = cMenu();
	menu.render();
	menu.render();
	window.display();

	// create game
	cGame game = cGame();


	// game loop
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            
			// treat events
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					std::cout << "new width: " << event.size.width << std::endl;
					std::cout << "new height: " << event.size.height << std::endl;
					break;
				case sf::Event::LostFocus:
					//game.pause();
					break;
				case sf::Event::GainedFocus:
					//game.resume();
					break;
				case sf::Event::KeyPressed:
					char c;
					switch (event.key.code) {
						case sf::Keyboard::A: c = 'A'; break;
						case sf::Keyboard::D: c = 'D'; break;
						case sf::Keyboard::S: c = 'S'; break;
						case sf::Keyboard::W: c = 'W'; break;
						case sf::Keyboard::Down: c = 'S'; break;
						case sf::Keyboard::Left: c = 'A'; break;
						case sf::Keyboard::Right: c = 'D'; break;
						case sf::Keyboard::Up: c = 'W'; break;
						case sf::Keyboard::Escape: window.close(); break;
						default: c = ' '; break;
					}
					game.keyPressed(c);
					break;
				case sf::Event::KeyReleased:
					//game.keyReleased(event.key.code);
					break;
				default:
					// nothing
					break;
			}
        }
		
		elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() > 1.0/60) { // 60 fps = 1.0/60
			window.setActive();
			game.update(clock.restart().asSeconds());
			game.render();
			window.display();
		}
    }

    return 0;
}
