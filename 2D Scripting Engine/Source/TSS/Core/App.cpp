#include "App.h"
#include "Utility/Util.h"
#include "Scripting/LuaManager.h"
#include "Rendering/TextureManager.h"

namespace TSS
{
	namespace Core
	{

		App::App(const char* windowTitle, int defaultWidth, int defaultHeight)
			: mWindow(NULL)
		{
			mWindow = new sf::RenderWindow(sf::VideoMode(defaultWidth, defaultHeight), windowTitle);
		}

		App::~App()
		{
			SAFE_DELETE(mWindow);
		}

		void App::Run()
		{
			// Init all singletons
			TSS::Rendering::TextureMgr::GetInstance()->Init();
			TSS::Scripting::LuaManager::GetInstance()->Init(mWindow);

			// Init our clock
			sf::Clock clock;

			//sf::CircleShape shape(100.f);
			//shape.setFillColor(sf::Color::Green);

			// Game Loop
			while (mWindow->isOpen())
			{
				sf::Time delta = clock.restart();
				float dt = delta.asSeconds();

				sf::Event event;
				while (mWindow->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						mWindow->close();
					}
					else if (event.type == sf::Event::TextEntered)
					{
						TSS::Scripting::LuaManager::GetInstance()->KeyPressed(static_cast<char>(event.text.unicode));
					}
					else if (event.type == sf::Event::KeyPressed)
					{
						TSS::Scripting::LuaManager::GetInstance()->KeyCodePressed(event.key.code);
					}
					else if (event.type == sf::Event::MouseButtonPressed)
					{
						TSS::Scripting::LuaManager::GetInstance()->MousePressed(event.mouseButton.button);
					}
				}

				TSS::Rendering::TextureMgr::GetInstance()->Update(dt);
				TSS::Scripting::LuaManager::GetInstance()->Update(dt);

				// Clear the our window
				mWindow->clear();
				//mWindow->draw(shape);

				// Let scripts render
				TSS::Scripting::LuaManager::GetInstance()->Render();

				// Display all our rendered objects
				mWindow->display();
			} // End Game Loop

			// clean up all singletons
			TSS::Scripting::LuaManager::GetInstance()->Shutdown();
			TSS::Rendering::TextureMgr::GetInstance()->Shutdown();
		}

	} // namespace Core
} // namespace TSS