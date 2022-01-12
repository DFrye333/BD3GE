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
		window->set_mouse_cursor_visibility(false);
		this->gl = new GL();
		this->gl->print_info();
		this->al = new AL();
		this->input = new Input(std::vector<Gamepad*>{ new XInputGamepad(0), new XInputGamepad(1) });

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
		Timer mouse_move_timer("Mouse Move", 10 * TICK_RATE);
		render_timer.start();
		logic_timer.start();
		mouse_move_timer.start();

		// Iterate endlessly (unless halted elsewhere).
		while (true) {
			// Handle subsystem communication.
			bus_messages();

			short primary_gamepad_index = input->get_primary_connected_gamepad_index();

			// Quits the program if necessary.
			if (!window->get_window_exists() || input->get_key_state(BD3GE::KEY_CODE::ESCAPE) || input->consume_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::UTIL_0)) {
				return;
			}

			// Enables toggling of wireframe mode.
			if (input->consume_key_input(BD3GE::KEY_CODE::F3) || input->consume_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::UTIL_1)) {
				gl->toggle_wireframe_mode();
			}

			// Check logic timer.
			if (logic_timer.is_due()) {
				// Process a logic tick.
				scene->tick(input);
			}

			// Check mouse drag timer.
			if (mouse_move_timer.is_due()) {
				// Process a logic tick.
				scene->mouse_move(input);
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
		Message<Window::InputEvent> window_input_message = window->pull_input_event();
		if (window_input_message.get_data() != nullptr) {
			input->handle(Window::InputEvent(*(window_input_message.get_data())));
		}

		input->update();

		// Pass window reshape events.
		Message<Window::ReshapeEvent> reshape_event = window->pull_reshape_event();
		if (reshape_event.get_data() != nullptr) {
			gl->reshape(reshape_event.get_data()->width, reshape_event.get_data()->height);
			scene->getCamera()->set_viewport(gl->get_viewport_width(), gl->get_viewport_height());
		}
	}
}