// Main 

#include "include/globals.hpp"
#include "include/cGame.hpp"

void initOpenGL() {

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	// Clear color screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//glEnable (GL_NORMALIZE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.1f, 1.0f);	

	// Cull triangles which normal is not towards the camera
	//glCullFace(GL_BACK);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	printf("iniOpenGL done correctly\n");
}

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

	initOpenGL();

	// create game
	cGame game;

	window.setActive();
	game.render();
	window.display();

	// load game assets
	game.loadAssets();

	// game loop
    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            char c = ' ';
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
					switch (event.key.code) {
						case sf::Keyboard::Num0: c = '0'; break;
						case sf::Keyboard::Num1: c = '1'; break;
						case sf::Keyboard::Num2: c = '2'; break;
						case sf::Keyboard::Num3: c = '3'; break;
						case sf::Keyboard::A: c = 'A'; break;
						case sf::Keyboard::D: c = 'D'; break;
						case sf::Keyboard::E: c = 'E'; break;
						case sf::Keyboard::N: c = 'N'; break;
						case sf::Keyboard::R: c = 'R'; break;
						case sf::Keyboard::S: c = 'S'; break;
						case sf::Keyboard::W: c = 'W'; break;
						case sf::Keyboard::Down: c = 'S'; break;
						case sf::Keyboard::Left: c = 'A'; break;
						case sf::Keyboard::Right: c = 'D'; break;
						case sf::Keyboard::Up: c = 'W'; break;
						case sf::Keyboard::Escape: window.close(); break;
						default: c = ' '; break;
					}
					window.setActive();
					game.keyPressed(c);
					if (game.getState() == STATE_QUIT) window.close();
					game.render();
					window.display();
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
