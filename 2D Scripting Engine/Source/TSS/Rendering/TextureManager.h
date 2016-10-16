#ifndef TSS_TEXTURE_MANAGER_H_
#define TSS_TEXTURE_MANAGER_H_

#include <SFML/Graphics.hpp>
#include "Scripting/ScriptingDefs.h"
#include "Utility/Util.h"
#include <vector>

namespace TSS
{
	namespace Rendering
	{

		struct TextureItem
		{
			TextureItem(const char* file)
			{
				mFile = file;
				if (mTex.loadFromFile(file))
				{
					mTex.setSmooth(true);
				}
			}

			std::string mFile;
			sf::Texture mTex;
		};

		class TextureMgr
		{
		public:
			typedef std::vector<TextureItem*> TextureList;

			void Init();
			void Shutdown();

			void Update(float dt);

			sf::Texture& LoadTexture(const char* file);

		private:

			TextureList mTextures;

			LAZY_SINGLETON(TextureMgr);
		};

	} // namespace Rendering
} // namespace TSS


#endif