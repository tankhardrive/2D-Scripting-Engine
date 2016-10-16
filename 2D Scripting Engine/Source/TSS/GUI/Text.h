#ifndef TSS_TEXT_H_
#define TSS_TEXT_H_

#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"

namespace TSS
{
	namespace GUI
	{

		class Text
		{
		public:

			Text();
			~Text();

			void SetCharSize(int size);
			void SetColor(sf::Color color);
			void SetStyle(int style);
			void SetText(const char* text);
			void SetPosition(int x, int y);
			
			void SetVisible(bool visible);
			bool IsVisible();

			void Draw();

			std::string GetText();

			static void RegisterWithLua();

		private:

			sf::Text mText;
			sf::Font mFont;
			bool mVisible;

		};

	} // namespace GUI
} // namespace TSS



#endif