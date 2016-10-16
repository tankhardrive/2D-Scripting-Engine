#include "LuaManager.h"
#include <iostream>
#include <stdio.h>

#include "GUI/Text.h"
#include "GUI/Color.h"
#include "Rendering/Circle.h"
#include "Rendering/Sprite.h"
#include "Rendering/IntRect.h"

namespace TSS
{
	namespace Scripting
	{

#define ENUM(enm) #enm

		LuaManager::LuaManager()
			: mLuaState(NULL)
		{

		}

		LuaManager::~LuaManager()
		{
			lua_close(mLuaState);
		}

		void LuaManager::Init(sf::RenderWindow* window)
		{
			// store off the render window
			mWindow = window;

			// Create our lua state and load the default libraries
			mLuaState = luaL_newstate();
			luaL_openlibs(mLuaState);

			// Define our engine object
			RunString("tss = { }");
			RunString("tss.gui = { }");
			RunString("tss.gui.colors = { }");
			RunString("tss.input = { }");  

			RegisterEnums();
			RegisterLuaFunctions();
			TSS::GUI::Text::RegisterWithLua();
			TSS::GUI::Color::RegisterWithLua();
			TSS::Rendering::Rect::RegisterWithLua();
			TSS::Rendering::Circle::RegisterWithLua();
			TSS::Rendering::Sprite::RegisterWithLua();



			// create console text field
			RunString("tss.consoleString = tss.gui.Text();");
			RunString("tss.consoleString:SetText('');");
			RunString("tss.consoleString:SetVisible(false);");
			RunString("tss.dt = 0;");

			// Load our main script, main.lua
			RunFile("Source/TSS/Scripting/EngineFuncs.lua");
			RunFile("Assets/Scripts/main.lua");

			// Call init
			luabridge::LuaRef tss = luabridge::getGlobal(mLuaState, "tss");

			if (tss["init"].isFunction())
			{
				tss["init"]();
			}
		}

		void LuaManager::ReloadLua()
		{			
			Shutdown();

			lua_close(mLuaState);
			mLuaState = NULL;

			Init(mWindow);
		}

		void LuaManager::Shutdown()
		{
			// Call shutdown
			luabridge::LuaRef shutdownTss = luabridge::getGlobal(mLuaState, "tss");

			if (shutdownTss["shutdown"].isFunction())
			{
				shutdownTss["shutdown"]();
			}

			shutdownTss = luabridge::Nil();
		}

		bool LuaManager::Update(float delta)
		{
			bool quit = false;

			// Call update
			luabridge::LuaRef tss = luabridge::getGlobal(mLuaState, "tss");

			char buffer[50];
			sprintf_s(buffer, 50, "tss.dt = %f", delta);
			RunString(buffer);

			if (tss["update"].isFunction())
			{
				quit = tss["update"](delta);
			}

			return quit;
		}

		void LuaManager::Render()
		{
			// Call draw
			luabridge::LuaRef tss = luabridge::getGlobal(mLuaState, "tss");

			if (tss["draw"].isFunction())
			{
				tss["draw"]();
			}

			if (tss["ConsoleDraw"].isFunction())
			{
				tss["ConsoleDraw"]();
			}
		}

		void LuaManager::KeyPressed(char key)
		{
			// Call KeyPressed
			luabridge::LuaRef tss = luabridge::getGlobal(mLuaState, "tss");

			if (_DEBUG && tss["ConsoleInput"].isFunction())
			{
				tss["ConsoleInput"](key);
			}

			if (tss["keyPressed"].isFunction())
			{
				tss["keyPressed"](key);
			}
		}

		void LuaManager::KeyCodePressed(sf::Keyboard::Key key)
		{
			// Call KeyCodePressed
			luabridge::LuaRef tss = luabridge::getGlobal(mLuaState, "tss");

			if (tss["keyCodePressed"].isFunction())
			{
				tss["keyCodePressed"](static_cast<int>(key));
			}

			tss = luabridge::Nil();

			// Need to check and reload all lua here otherwise we will crash if we try to do it from script
			if (key == sf::Keyboard::F5 && _DEBUG)
			{
				TSS::Scripting::LuaManager::GetInstance()->ReloadLua();
			}
		}

		void LuaManager::RunFile(const char* file)
		{
			ReportErrors(luaL_dofile(mLuaState, file));
		}

		void LuaManager::RunString(const char* str)
		{
			ReportErrors(luaL_dostring(mLuaState, str));
		}

		bool LuaManager::ReportErrors(int status)
		{
			if (status != 0)
			{
				std::cerr << "-- " << lua_tostring(mLuaState, -1) << std::endl;
				lua_pop(mLuaState, 1); // Remove error message
				return true;
			}

			return false;
		}

		void LuaManager::SetWindowTitle(const char* title)
		{
			mWindow->setTitle(title);
		}

		void LuaManager::SetWindowSize(int width, int height)
		{
			mWindow->setSize(sf::Vector2u(width, height));
		}

		bool LuaManager::IsKeyDown(sf::Keyboard::Key key)
		{
			return sf::Keyboard::isKeyPressed(key);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Static functions below this
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static void StaticWindowTitle(const char* title)
		{
			TSS::Scripting::LuaManager::GetInstance()->SetWindowTitle(title);
		}

		static void StaticSetWindowSize(int width, int height)
		{
			TSS::Scripting::LuaManager::GetInstance()->SetWindowSize(width, height);
		}

		static void StaticRunString(const char* strn)
		{
			TSS::Scripting::LuaManager::GetInstance()->RunString(strn);
		}

		static void StaticRunFile(const char* file)
		{
			TSS::Scripting::LuaManager::GetInstance()->RunFile(file);
		}

		static bool StaticIsKeyDown(int key)
		{
			return TSS::Scripting::LuaManager::GetInstance()->IsKeyDown(static_cast<sf::Keyboard::Key>(key));
		}

		// Register functions with lua
		void LuaManager::RegisterLuaFunctions()
		{
			luabridge::getGlobalNamespace(mLuaState)
				.beginNamespace("tss")
					.beginNamespace("engine")
						.addFunction("SetWindowTitle", &StaticWindowTitle)
						.addFunction("SetWindowSize", &StaticSetWindowSize)
						.addFunction("IsKeyDown", &StaticIsKeyDown)
					.endNamespace()
					.beginNamespace("scripting")
						.addFunction("RunString", &StaticRunString)
						.addFunction("RunFile", &StaticRunFile)
					.endNamespace()
				.endNamespace();
		}





		void LuaManager::RegisterEnums()
		{
			RunString("tss.input.unknown = -1;");
			RunString("tss.input.a = 0;");
			RunString("tss.input.b = 1;");
			RunString("tss.input.c = 2;");
			RunString("tss.input.d = 3;");
			RunString("tss.input.e = 4;");
			RunString("tss.input.f = 5;");
			RunString("tss.input.g = 6;");
			RunString("tss.input.h = 7;");
			RunString("tss.input.i = 8;");
			RunString("tss.input.j = 9;");
			RunString("tss.input.k = 10;");
			RunString("tss.input.l = 11;");
			RunString("tss.input.m = 12;");
			RunString("tss.input.n = 13;");
			RunString("tss.input.o = 14;");
			RunString("tss.input.p = 15;");
			RunString("tss.input.q = 16;");
			RunString("tss.input.r = 17;");
			RunString("tss.input.s = 18;");
			RunString("tss.input.t = 19;");
			RunString("tss.input.u = 20;");
			RunString("tss.input.v = 21;");
			RunString("tss.input.w = 22;");
			RunString("tss.input.x = 23;");
			RunString("tss.input.y = 24;");
			RunString("tss.input.z = 25;");
			RunString("tss.input.num0 = 26;");
			RunString("tss.input.num1 = 27;");
			RunString("tss.input.num2 = 28;");
			RunString("tss.input.num3 = 29;");
			RunString("tss.input.num4 = 30;");
			RunString("tss.input.num5 = 31;");
			RunString("tss.input.num6 = 32");
			RunString("tss.input.num7 = 33;");
			RunString("tss.input.num8 = 34;");
			RunString("tss.input.num9 = 35;");
			RunString("tss.input.escape = 36;");
			RunString("tss.input.lcontrol = 37;");
			RunString("tss.input.lshift = 38;");
			RunString("tss.input.lalt = 39;");
			RunString("tss.input.lsystem = 40;");
			RunString("tss.input.rcontrol = 41;");
			RunString("tss.input.rshift = 42;");
			RunString("tss.input.ralt = 43;");
			RunString("tss.input.rsystem = 44;");
			RunString("tss.input.menu = 45;");
			RunString("tss.input.lbracket = 46;");
			RunString("tss.input.rbracket = 47;");
			RunString("tss.input.semicolon = 48;");
			RunString("tss.input.comma = 49;");
			RunString("tss.input.period = 50;");
			RunString("tss.input.quote = 51;");
			RunString("tss.input.slash = 52;");
			RunString("tss.input.backslash = 53;");
			RunString("tss.input.tilde = 54;");
			RunString("tss.input.equal = 55;");
			RunString("tss.input.dash = 56;");
			RunString("tss.input.space = 57;");
			RunString("tss.input.returnKey = 58;");
			RunString("tss.input.backspace = 59;");
			RunString("tss.input.tab = 60;");
			RunString("tss.input.pageup = 61;");
			RunString("tss.input.pagedown = 62;");
			RunString("tss.input.endKey = 63;");
			RunString("tss.input.home = 64;");
			RunString("tss.input.insert = 65;");
			RunString("tss.input.delete = 66;");
			RunString("tss.input.add = 67;");
			RunString("tss.input.subtract = 68;");
			RunString("tss.input.multiply = 69;");
			RunString("tss.input.divide = 70;");
			RunString("tss.input.left = 71;");
			RunString("tss.input.right = 72;");
			RunString("tss.input.up = 73;");
			RunString("tss.input.down = 74;");
			RunString("tss.input.numpad0 = 75;");
			RunString("tss.input.numpad1 = 76;");
			RunString("tss.input.numpad2 = 77;");
			RunString("tss.input.numpad3 = 78;");
			RunString("tss.input.numpad4 = 79;");
			RunString("tss.input.numpad5 = 80;");
			RunString("tss.input.numpad6 = 81;");
			RunString("tss.input.numpad7 = 82;");
			RunString("tss.input.numpad8 = 83;");
			RunString("tss.input.numpad9 = 84;");
			RunString("tss.input.f1 = 85;");
			RunString("tss.input.f2 = 86;");
			RunString("tss.input.f3 = 87;");
			RunString("tss.input.f4 = 88;");
			RunString("tss.input.f5 = 89;");
			RunString("tss.input.f6 = 90;");
			RunString("tss.input.f7 = 91;");
			RunString("tss.input.f8 = 92;");
			RunString("tss.input.f9 = 93;");
			RunString("tss.input.f10 = 94;");
			RunString("tss.input.f11 = 95;");
			RunString("tss.input.f12 = 96;");
			RunString("tss.input.f13 = 97;");
			RunString("tss.input.f14 = 98;");
			RunString("tss.input.f15 = 99;");
			RunString("tss.input.pause = 100;");
			RunString("tss.input.keycount = 101;");
		}

	} // namespace Scripting
} // namespace TSS