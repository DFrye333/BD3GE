#include "game.h"

namespace BD3GE {
	Game::Game(BD3GE::Window* window) {
		g_log.write(BD3GE::LOG_TYPE::INFO, "Starting up BD3GE now...");

		DIR* default_system_directory_stream = opendir(DEFAULT_SYSTEM_DIRECTORY.c_str());
		if (!default_system_directory_stream) {
			// TODO: Ugly! Create a class to handle filesystem stuff.
#ifdef __linux__
			if (-1 == mkdir(DEFAULT_SYSTEM_DIRECTORY.c_str(), S_IRWXU | S_IRWXG | S_IROTH)) {
#elif _WIN32
			if (-1 == _mkdir(DEFAULT_SYSTEM_DIRECTORY.c_str())) {
#endif
				g_log.write(BD3GE::LOG_TYPE::ERR, "System directory creation failure.");
			}
		}
		closedir(default_system_directory_stream);

		// TODO: Consider platform independence here.
		this->window = window;
		//window->set_mouse_cursor_visibility(false);
		this->gl = new GL();
		this->gl->print_info();
		this->al = new AL();
		this->input = new Input();

		glewExperimental = GL_TRUE;
		glewInit();

		this->scene = new Scene(DEFAULT_RESOURCE_DIRECTORY + "models/");
	}

	Game::~Game() {
		g_log.write(BD3GE::LOG_TYPE::INFO, "Shutting down BD3GE now...");

		delete window;
		window = nullptr;

		delete gl;
		gl = nullptr;

		delete al;
		al = nullptr;

		delete input;
		input = nullptr;

		delete scene;
		scene = nullptr;
	}

	void Game::run() {
		//    Main game loop
		// ========================================================================

		// Initialize the logic and rendering timers.
		Timer render_timer("Render", FRAME_RATE);
		Timer logic_timer("Logic", TICK_RATE);
		render_timer.start();
		logic_timer.start();

		// Iterate endlessly (unless halted elsewhere).
		while (true) {
			// Handle subsystem communication.
			bus_messages();

			// Quit the program if the Escape key is pressed.
			if (input->get_key_state(BD3GE::KEY_CODE::ESCAPE)) {
				return;
			}

			// Enables toggling of wireframe mode.
			if (input->consume_key_input(BD3GE::KEY_CODE::F3)) {
				gl->toggle_wireframe_mode();
			}

			// Check logic timer.
			if (logic_timer.is_due()) {
				// Process a logic tick.
				scene->tick(input);
			}

			// Check render timer.
			if (render_timer.is_due()) {
				//std::cout << "FRAME" << std::endl;

				// Process a rendering frame.
				scene->render();

				// Swap the frame buffers.
				window->swap_buffers();
			}
		}
		// ========================================================================
	}

	void Game::bus_messages() {
		// Listen for window messages.
		window->message_listener();

		// Pass window input events.
		input->handle(window->pull_input_event());

		// Pass window reshape events.
		Window::ReshapeEvent reshape_event = window->pull_reshape_event();
		gl->reshape(reshape_event.width, reshape_event.height);
		scene->getCamera()->set_viewport(gl->get_viewport_width(), gl->get_viewport_height());
	}
}