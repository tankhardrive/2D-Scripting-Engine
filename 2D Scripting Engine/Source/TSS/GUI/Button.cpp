#include "Button.h"
#include "Utility/Util.h"
#include "Scripting/LuaManager.h"
#include "Rendering/IntRect.h"
#include "Rendering/TextureManager.h"

namespace TSS
{
	namespace GUI
	{

		Button::Button()
			: mPressedCallback(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
		{
			// Register with a manager
		}

		Button::~Button()
		{
			// unregister with the manager
		}

		void Button::SetCharSize(int size)
		{
			mText.setCharacterSize(size);
		}

		void Button::SetColor(sf::Color color)
		{
			mText.setColor(color);
		}

		void Button::SetStyle(int style)
		{
			mText.setStyle(style);
		}

		void Button::SetText(const char* text)
		{
			mText.setString(text);
		}

		void Button::SetPosition(int x, int y)
		{
			mSprite.setPosition(sf::Vector2f(x, y));
			mText.setPosition(sf::Vector2f(x, y));
		}

		void Button::SetVisible(bool visible)
		{
			mVisible = visible;
		}

		bool Button::IsVisible()
		{
			return mVisible;
		}

		void Button::Draw()
		{
			if (mVisible)
			{
				TSS::Scripting::LuaManager::GetInstance()->GetRenderWindow()->draw(mSprite);
				TSS::Scripting::LuaManager::GetInstance()->GetRenderWindow()->draw(mText);
			}
		}

		void Button::SetBackground(const char* filename)
		{
			mSprite.setTexture(TSS::Rendering::TextureMgr::GetInstance()->LoadTexture(filename));
		}

		std::string Button::GetText()
		{
			return mText.getString().toAnsiString();
		}

		void Button::SetPressedCallback(luabridge::LuaRef callback)
		{
			mPressedCallback = callback;
		}

		void Button::ButtonPressed(sf::Mouse::Button button)
		{
			if (mPressedCallback.isFunction())
			{
				mPressedCallback(static_cast<int>(button));
			}
		}

		void Button::SetSize(int width, int height)
		{
			
		}


		void Button::RegisterWithLua()
		{
			luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
				.beginNamespace("tss")
					.beginNamespace("gui")
						.beginClass<TSS::GUI::Button>("Button")
							.addConstructor<void(*) (void)>()
							.addFunction("SetCharSize", &Button::SetCharSize)
							.addFunction("SetColor", &Button::SetColor)
							.addFunction("SetStyle", &Button::SetStyle)
							.addFunction("SetText", &Button::SetText)
							.addFunction("SetPosition", &Button::SetPosition)
							.addFunction("Draw", &Button::Draw)
							.addFunction("SetVisible", &Button::SetVisible)
							.addFunction("IsVisible", &Button::IsVisible)
							.addFunction("GetText", &Button::GetText)
							.addFunction("SetBackground", &Button::SetBackground)
							.addFunction("SetPressedCallback", &Button::SetPressedCallback)
							.addFunction("SetSize", &Button::SetSize)
						.endClass()
					.endNamespace()
				.endNamespace();
		}

	} // namespace GUI
} // namespace TSS