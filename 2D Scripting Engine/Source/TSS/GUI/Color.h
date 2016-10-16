#ifndef TSS_COLOR_H_
#define TSS_COLOR_H_

// This is a wrapper for sfml color for scripting

#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"
#include "Scripting/LuaManager.h"

namespace TSS
{
	namespace GUI
	{
		namespace Color
		{

			static void RegisterWithLua()
			{
				luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
					.beginNamespace("tss")
						.beginNamespace("gui")
							.beginClass<sf::Color>("Color")
								.addConstructor<void(*) (void)>()
								.addConstructor<void(*) (int, int, int, int)>()
								.addData("r", &sf::Color::r)
								.addData("g", &sf::Color::g)
								.addData("b", &sf::Color::b)
								.addData("a", &sf::Color::a)
							.endClass()
						.endNamespace()
					.endNamespace();
			}

		} // namespace Color
	} // namespace GUI
} // namespace TSS

#endif