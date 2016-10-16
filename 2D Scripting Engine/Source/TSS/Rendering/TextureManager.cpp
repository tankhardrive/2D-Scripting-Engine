#include "TextureManager.h"



namespace TSS
{
	namespace Rendering
	{

		TextureMgr::TextureMgr()
		{

		}

		TextureMgr::~TextureMgr()
		{

		}

		void TextureMgr::Init()
		{

		}

		void TextureMgr::Shutdown()
		{
			TextureList::iterator itr = mTextures.begin();
			TextureList::iterator end = mTextures.end();
			for (; itr != end; ++itr)
			{
				delete (*itr);
				(*itr) = NULL;
			}
			mTextures.clear();
		}

		void TextureMgr::Update(float dt)
		{

		}

		sf::Texture& TextureMgr::LoadTexture(const char* file)
		{
			TextureList::iterator itr = mTextures.begin();
			TextureList::iterator end = mTextures.end();
			for (; itr != end; ++itr)
			{
				if ((*itr)->mFile == file)
				{
					return (*itr)->mTex;
				}
			}

			TextureItem* tex = new TextureItem(file);
			mTextures.push_back(tex);

			return tex->mTex;
		}

	} // namespace Rendering
} // namespace TSS