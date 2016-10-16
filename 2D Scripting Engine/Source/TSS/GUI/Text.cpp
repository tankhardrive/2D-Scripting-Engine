#include "Text.h"
#include "Utility/Util.h"
#include "Scripting/LuaManager.h"


namespace TSS
{
	namespace GUI
	{

		Text::Text()
			: mVisible(true)
		{
			if (!mFont.loadFromFile("Assets/Fonts/consola.ttf"))
			{
				//ASSERT(false, "Failed to load font: consola.ttf");
			}

			mText.setFont(mFont);
			mText.setString("");
		}

		Text::~Text()
		{

		}

		void Text::SetCharSize(int size)
		{
			mText.setCharacterSize(size);
		}

		void Text::SetColor(sf::Color color)
		{
			mText.setColor(color);
		}

		void Text::SetStyle(int style)
		{
			mText.setStyle(style);
		}

		void Text::SetText(const char* text)
		{
			mText.setString(text);
		}

		void Text::SetPosition(int x, int y)
		{
			mText.setPosition(sf::Vector2f(x, y));
		}

		void Text::SetVisible(bool visible)
		{
			mVisible = visible;
		}

		bool Text::IsVisible()
		{
			return mVisible;
		}

		void Text::Draw()
		{
			TSS::Scripting::LuaManager::GetInstance()->GetRenderWindow()->draw(mText);
		}

		std::string Text::GetText()
		{
			return mText.getString().toAnsiString();
		}

		void Text::RegisterWithLua()
		{
			luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
				.beginNamespace("tss")
					.beginNamespace("gui")
						.beginClass<TSS::GUI::Text>("Text")
							.addConstructor<void(*) (void)>()
							.addFunction("SetCharSize", &Text::SetCharSize)
							.addFunction("SetColor", &Text::SetColor)
							.addFunction("SetStyle", &Text::SetStyle)
							.addFunction("SetText", &Text::SetText)
							.addFunction("SetPosition", &Text::SetPosition)
							.addFunction("Draw", &Text::Draw)
							.addFunction("SetVisible", &Text::SetVisible)
							.addFunction("IsVisible", &Text::IsVisible)
							.addFunction("GetText", &Text::GetText)
						.endClass()
					.endNamespace()
				.endNamespace();
		}

	} // namespace GUI
} // namespace TSS
