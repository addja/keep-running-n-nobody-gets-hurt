// Main 

#include "include/globals.hpp"
#include "include/cGame.hpp"

int main() {
	// create window and initialize it
    sf::RenderWindow window(sf::VideoMode(WNDW_WIDTH, WNDW_HEIGHT), GAME_TITLE);

    sf::Event event;
	window.setKeyRepeatEnabled(false); // not count key holding press
	sf::Clock clock;
	sf::Time elapsed;

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
					//game.keyPressed(event.key.code);
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
			game.update(clock.restart().asSeconds());
			game.render();
			window.display();
		}
    }

    return 0;
}
