#include "game.h"

namespace BD3GE
{
	/*
	 *	Game class
	 */

	Game::~Game()
	{
		shutdown();
	}

	void Game::startup(void)
	{
		m_running = false;
		
		if (!m_running)
		{
			g_log.write("Starting up BD3GE now...", LOG_INFORMATION);

			m_running = true;

			DIR* default_system_directory_stream = opendir(DEFAULT_SYSTEM_DIRECTORY.c_str());
			if (!default_system_directory_stream)
			{
				if (-1 == mkdir(DEFAULT_SYSTEM_DIRECTORY.c_str(), S_IRWXU | S_IRWXG | S_IROTH))
				{
					g_log.write("System directory creation failure.", LOG_ERROR);
				}
			}
			closedir(default_system_directory_stream);

			// The below initialization order matters! For instance, if m_XWindow is placed after (and therefore initialized after) m_GL, the OpenGL context is not properly set up.
			// TODO: Consider platform independence here.
			m_window = new X_Window;
			m_GL = new GL;
			m_AL = new AL;
			m_input = new Input;

			glewInit();
			
			m_scene = new Scene("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/mesh/cube.dae");
			// m_scene = new Scene("/home/david/Development/Eclipse Workspace/Game Prototype 0/resource/mesh/duck.dae");
		}
	}

	void Game::shutdown(void)
	{
		if (m_running)
		{
			g_log.write("Shutting down BD3GE now...", LOG_INFORMATION);

			m_running = false;
		}

		delete m_window;
		m_window = NULL;

		delete m_GL;
		m_GL = NULL;

		delete m_AL;
		m_AL = NULL;

		delete m_input;
		m_input = NULL;

		delete m_scene;
		m_scene = NULL;
	}

	void Game::run(void)
	{
		//    Main game loop
		// ========================================================================

		// Initialize the logic and rendering timers.
		float elapsed_time = 0.0f;
		Timer render_timer("Render", FRAME_TIME);
		Timer logic_timer("Logic", TICK_TIME);
		render_timer.start();
		logic_timer.start();

		// Iterate endlessly (unless halted elsewhere).
		while (m_running)
		{
			// Handle subsystem communication.
			bus_messages();

			// Quit the program if the Escape key is pressed.
			if (m_input->get_key_state(KEY_ESCAPE))
			{
				shutdown();

				continue;
			}

			// Check logic timer.
			if (logic_timer.is_due())
			{
				// Process a logic tick.
				m_scene->tick(m_input);
			}

			// Check render timer.
			if (render_timer.is_due(&elapsed_time))
			{
				// Process a rendering frame.
				m_scene->render();

				// Swap the frame buffers.
				m_window->swap_buffers();

				// Display FPS.
				// std::cout << "FPS: " << 1 / (elapsed_time / 1000.0f) << std::endl;
			}
		}
		// ========================================================================
	}

	void Game::bus_messages(void)
	{
		// Listen for X messages.
		m_window->message_listener();

		// Pass input events.
		Message< std::pair<std::string, bool> > input_message = m_window->pull_input_message();
		if (input_message.get_data())
		{
			m_input->handler(input_message);
		}

		// Pass reshape events.
		Message< std::pair<int, int> > reshape_message = m_window->pull_reshape_message();
		if (reshape_message.get_data())
		{
			m_GL->reshape(reshape_message.get_data()->first, reshape_message.get_data()->second);
			m_scene->getCamera().set_viewport(m_GL->get_viewport_width(), m_GL->get_viewport_height());
		}
	}
}