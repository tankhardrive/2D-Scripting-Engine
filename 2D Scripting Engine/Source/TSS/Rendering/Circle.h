#ifndef TSS_CIRCLE_H_
#define TSS_CIRCLE_H_


#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"
#include "Scripting/LuaManager.h"


namespace TSS
{
	namespace Rendering
	{
		namespace Circle
		{

			class TssCircle : public sf::CircleShape
			{
			public:

				TssCircle() : sf::CircleShape() { }
				TssCircle(float rad) : sf::CircleShape(rad) { }
				TssCircle(float rad, size_t points) : sf::CircleShape(rad, points) { }

				~TssCircle() { }

				void setPosition(int x, int y)
				{
					sf::CircleShape::setPosition(sf::Vector2f(x, y));
				}

				void setOutlineColor(sf::Color color)
				{
					sf::CircleShape::setOutlineColor(color);
				}

				void setFillColor(sf::Color color)
				{
					sf::CircleShape::setFillColor(color);
				}

				float getPosX()
				{
					return sf::CircleShape::getPosition().x;
				}

				void setPosX(float x)
				{
					sf::CircleShape::setPosition(sf::Vector2f(x, sf::CircleShape::getPosition().y));
				}

				int getPosY()
				{
					return sf::CircleShape::getPosition().y;
				}

				void setPosY(float y)
				{
					sf::CircleShape::setPosition(sf::Vector2f(sf::CircleShape::getPosition().x, y));
				}

				void Draw()
				{
					TSS::Scripting::LuaManager::GetInstance()->GetRenderWindow()->draw(*this);
				}

				void setOutlineThickness(float thick)
				{
					sf::CircleShape::setOutlineThickness(thick);
				}

				void setRadius(float rad)
				{
					sf::CircleShape::setRadius(rad);
				}

			};

			static void RegisterWithLua()
			{
				luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
					.beginNamespace("tss")
						.beginNamespace("rendering")
							.beginClass<TssCircle>("Circle")
								.addConstructor<void(*) (void)>()
								.addConstructor<void(*) (float)>()
								.addFunction("SetRadius", &TssCircle::setRadius)
								.addFunction("SetOutlineThickness", &TssCircle::setOutlineThickness)
								.addFunction("SetFillColor", &TssCircle::setFillColor)
								.addFunction("SetOutlineColor", &TssCircle::setOutlineColor)
								.addFunction("SetPosition", &TssCircle::setPosition)
								.addFunction("GetPosX", &TssCircle::getPosX)
								.addFunction("SetPosX", &TssCircle::setPosX)
								.addFunction("GetPosY", &TssCircle::getPosY)
								.addFunction("SetPosY", &TssCircle::setPosY)
								.addFunction("Draw", &TssCircle::Draw)
							.endClass()
						.endNamespace()
					.endNamespace();
			}

		} // namespace Circle
	} // namespace Rendering
} // namespace TSS

#endif