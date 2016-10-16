#ifndef TSS_INTRECT_H_
#define TSS_INTRECT_H_


#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"
#include "Scripting/LuaManager.h"


namespace TSS
{
	namespace Rendering
	{
		namespace Rect
		{

			class IntRect : public sf::IntRect
			{
			public:

				IntRect(int x, int y, int w, int h) : sf::IntRect(x, y, w, h) { }

				~IntRect() { }

			};


			static void RegisterWithLua()
			{
				luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
					.beginNamespace("tss")
						.beginNamespace("rendering")
							.beginClass<IntRect>("IntRect")
								.addConstructor<void(*) (int, int, int, int)>()
							.endClass()
						.endNamespace()
					.endNamespace();
			}

		} // namespace Rect
	} // namespace Rendering
} // namespace TSS


#endif