#ifndef TSS_BUTTON_H_
#define TSS_BUTTON_H_

#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"

namespace TSS
{
	namespace GUI
	{

		class Button
		{
		public:

			Button();
			~Button();

			void SetCharSize(int size);
			void SetColor(sf::Color color);
			void SetStyle(int style);
			void SetText(const char* text);
			void SetPosition(int x, int y);

			void SetVisible(bool visible);
			bool IsVisible();

			void SetBackground(const char* filename);

			void SetPressedCallback(luabridge::LuaRef callback);
			void ButtonPressed(sf::Mouse::Button button);

			void SetSize(int width, int height);

			void Draw();

			std::string GetText();

			static void RegisterWithLua();

		private:

			sf::Sprite mSprite;
			sf::Text mText;
			sf::Font mFont;
			luabridge::LuaRef mPressedCallback;
			bool mVisible;

		};

	} // namespace GUI
} // namespace TSS


#endif // TSS_BUTTON_H_