#include "game.h"

namespace BD3GE {
	Log* g_log;

	Game::Game(Window* window) : window(window), scene(nullptr) {
//#ifdef __linux__
//			if (-1 == mkdir(DEFAULT_RELATIVE_SYSTEM_DIRECTORY.c_str(), S_IRWXU | S_IRWXG | S_IROTH))

		std::string system_directory_path = WinAPI::get_environment_variable("LOCALAPPDATA") + "/" + DEFAULT_RELATIVE_SYSTEM_DIRECTORY;
		std::string log_directory_path = system_directory_path + DEFAULT_LOG_DIRECTORY;
		if (!WinAPI::does_directory_exist(log_directory_path)) {
			std::string result;
			bool success = WinAPI::make_directory(system_directory_path, result);
			if (!success) {
				std::cout << "System directory creation failure: " + result << std::endl;
			}

			success = WinAPI::make_directory(log_directory_path, result);

			g_log = new Log(log_directory_path);
			g_log->write(Log::TYPE::INFO, "Starting up BD3GE now...");

			success ? g_log->write(Log::TYPE::INFO, "Log directory creation success at: " + log_directory_path) : g_log->write(Log::TYPE::ERR, "Log directory creation failure: " + result);
		} else {
			g_log = new Log(log_directory_path);
			g_log->write(Log::TYPE::INFO, "Starting up BD3GE now...");
		}

		this->window->set_mouse_cursor_visibility(false);
		this->renderer = new Renderer();
		this->al = new AL();
		this->input = new Input(std::vector<Gamepad*>{ new XInputGamepad(0), new XInputGamepad(1) });

		glewExperimental = GL_TRUE;
		glewInit();
	}

	Game::~Game() {
		g_log->write(Log::TYPE::INFO, "Shutting down BD3GE now...");

		delete window;
		window = nullptr;

		delete al;
		al = nullptr;

		delete renderer;
		renderer = nullptr;

		delete input;
		input = nullptr;

		delete scene;
		scene = nullptr;
	}

	void Game::load_scene(Scene* scene) {
		this->scene = scene;
		this->renderer->load_scene(scene);
	}

	void Game::run() {
		//    Main game loop
		// ========================================================================

		// Initialize the logic and rendering timers.
		Timer* render_timer = new WinAPITimer("Render", FRAME_RATE);
		Timer* logic_timer = new WinAPITimer("Logic", TICK_RATE);
		Timer* mouse_move_timer = new WinAPITimer("Mouse Move", TICK_RATE);
		render_timer->start();
		logic_timer->start();
		mouse_move_timer->start();

		// Iterate endlessly (unless halted elsewhere).
		while (true) {
			// Handle subsystem communication.
			bus_messages();

			short primary_gamepad_index = input->get_primary_connected_gamepad_index();

			// Quits the program if necessary.
			if (!window->get_window_exists() || input->get_key_state(BD3GE::KEY_CODE::ESCAPE) || input->consume_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::UTIL_1)) {
				return;
			}
			// Pauses the program if necessary.
			if (input->get_key_state(BD3GE::KEY_CODE::F1) || input->consume_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::UTIL_0)) {
				logic_timer->toggle_pause();
			}

			if (scene) {
				// Check logic timer.
				if (logic_timer->is_due()) {
					// Process a logic tick.
					tick(input);
				}

				// Check mouse drag timer.
				if (mouse_move_timer->is_due()) {
					// Process a mouse move tick.
					// TODO: Figure out a better solution for these rigid calls - they should probably be callbacks from the game?
					mouse_move(input);
				}
			}

			if (renderer) {
				// Enables toggling of wireframe mode.
				if (input->consume_key_input(BD3GE::KEY_CODE::F3) || input->consume_gamepad_input_value(primary_gamepad_index, BD3GE::Gamepad::INPUT_CODE::FACE_3)) {
					renderer->toggle_wireframe_mode();
				}

				// Check render timer.
				if (render_timer->is_due()) {
					// Process a rendering frame.
					renderer->render();

					// Swap the frame buffers.
					window->swap_buffers();
				}
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
			renderer->reshape_viewport(reshape_event.get_data()->width, reshape_event.get_data()->height);
		}
	}
}