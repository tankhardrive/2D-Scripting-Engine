#ifndef TSS_CORE_APP_H_
#define TSS_CORE_APP_H_

#include <SFML/Graphics.hpp>

namespace TSS
{
	namespace Core
	{

		class App
		{
		public:

			App(const char* windowTitle, int defaultWidth, int defaultHeight);
			~App();

			void Run();

		private:

			sf::RenderWindow* mWindow;

		};

	} // namespace Core
} // namespace TSS


#endif