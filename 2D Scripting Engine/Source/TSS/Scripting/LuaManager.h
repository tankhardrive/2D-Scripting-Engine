#ifndef TSS_SCRIPTING_LUAMANAGER_H_
#define TSS_SCRIPTING_LUAMANAGER_H_

#include <SFML/Graphics.hpp>
#include "Utility/Util.h"
#include "Scripting/ScriptingDefs.h"

namespace TSS
{
	namespace Scripting
	{

		class LuaManager
		{
		public:

			void Init(sf::RenderWindow* window);
			void Shutdown();

			bool Update(float delta);
			void Render();

			void KeyPressed(char key);
			void KeyCodePressed(sf::Keyboard::Key key);

			void RunString(const char* str);
			void RunFile(const char* file);

			lua_State* GetLuaState() { return mLuaState; }
			sf::RenderWindow* GetRenderWindow() { return mWindow; }

			void SetWindowTitle(const char* title);
			void SetWindowSize(int width, int height);

			bool IsKeyDown(sf::Keyboard::Key key);

			void ReloadLua();

		private:

			void RegisterLuaFunctions();
			void RegisterEnums();

			bool ReportErrors(int status);

			lua_State* mLuaState;
			sf::RenderWindow* mWindow;

			LAZY_SINGLETON(LuaManager);
		};

	} // namespace Scripting
} // namespace TSS

#endif