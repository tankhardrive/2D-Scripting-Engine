#ifndef TSS_SPRITE_H_
#define TSS_SPRITE_H_

#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"
#include "Scripting/LuaManager.h"
#include "Rendering/IntRect.h"

namespace TSS
{
	namespace Rendering
	{
		namespace Sprite
		{

			class Sprite : public sf::Sprite
			{
			public:

				Sprite() :sf::Sprite() { }
				Sprite(const char* file) :sf::Sprite()
				{
					if (mTex.loadFromFile(file))
					{
						mTex.setSmooth(true);
						sf::Sprite::setTexture(mTex);
					}
				}

				~Sprite() { mTex.bind(NULL); }

				void loadTexture(const char* file)
				{
					if (mTex.loadFromFile(file))
					{
						mTex.setSmooth(true);
						sf::Sprite::setTexture(mTex);
					}
				}

				void Draw()
				{
					TSS::Scripting::LuaManager::GetInstance()->GetRenderWindow()->draw(*this);
				}

				void setColor(sf::Color color)
				{
					sf::Sprite::setColor(color);
				}

				void setRotation(float rot)
				{
					sf::Sprite::setRotation(rot);
				}

				void rotate(float rot)
				{
					sf::Sprite::rotate(rot);
				}

				void setPosition(float x, float y)
				{
					sf::Sprite::setPosition(x, y);
				}

				void move(float x, float y)
				{
					sf::Sprite::move(x, y);
				}

				void setOrigin(float x, float y)
				{
					sf::Sprite::setOrigin(x, y);
				}

				void setScale(float xScale, float yScale)
				{
					sf::Sprite::setScale(xScale, yScale);
				}

				void scale(float xScale, float yScale)
				{
					sf::Sprite::scale(xScale, yScale);
				}

				void setTextureRect(TSS::Rendering::Rect::IntRect rect)
				{
					sf::Sprite::setTextureRect(rect);
				}

			private:

				// this texture should live in a manager class so we don't load a new image for every sprite
				sf::Texture mTex;

			};



			static void RegisterWithLua()
			{
				luabridge::getGlobalNamespace(TSS::Scripting::LuaManager::GetInstance()->GetLuaState())
					.beginNamespace("tss")
						.beginNamespace("rendering")
							.beginClass<Sprite>("Sprite")
								.addConstructor<void(*) (void)>()
								.addConstructor<void(*) (const char*)>()
								.addFunction("LoadTexture", &Sprite::loadTexture)
								.addFunction("Draw", &Sprite::Draw)
								.addFunction("setColor", &Sprite::setColor)
								.addFunction("SetRotation", &Sprite::setRotation)
								.addFunction("Rotate", &Sprite::rotate)
								.addFunction("SetPosition", &Sprite::setPosition)
								.addFunction("Move", &Sprite::move)
								.addFunction("SetOrigin", &Sprite::setOrigin)
								.addFunction("SetScale", &Sprite::setScale)
								.addFunction("Scale", &Sprite::scale)
								.addFunction("SetTextureRect", &Sprite::setTextureRect)
							.endClass()
						.endNamespace()
					.endNamespace();
			}

		} // namespace Sprite
	} // namespace Rendering
} // namespace TSS

#endif