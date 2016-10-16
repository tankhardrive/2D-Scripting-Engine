#include "Core/App.h"

int main()
{
	TSS::Core::App game("test game", 800, 600);

	game.Run();

	return 0;
}