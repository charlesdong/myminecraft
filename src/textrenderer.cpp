#include "textrenderer.h"
#include "texturemanager.h"

TextRenderer::TextRenderer()
{
}

void TextRenderer::init(BidimensionalRenderer * pBidRenderer)
{
	bidRenderer = pBidRenderer;
	idTexUnicode00 = TextureManager::load("font/unicode_page_00.png");
}

void TextRenderer::render(const char * text) const
{
	TextureManager::get(idTexUnicode00).bind();
	const int sizeX = 6;
	const int sizeY = 10;
	int posX = 0;
	int posY = 600 - sizeY;
	for (const char * pc = text; *pc != '\0'; pc++)
	{
		if (*pc != '\n')
		{
			if (*pc != ' ')
			{
				int xi = (int)*pc % 16;
				int yi = 15 - (int)*pc / 16;
				// TODO: MagNum
				bidRenderer->render(
					glm::ivec2(posX, posY),
					glm::ivec2(sizeX, sizeY),
					(float)(xi + 0.0625) / 16.0f,
					(float)(xi + 0.4375) / 16.0f,
					(float)(yi + 0.125) / 16.0f,
					(float)(yi + 0.75) / 16.0f,
					false
				);
			}
			posX += sizeX;		// advance the X position
			posX += 4;
		}
		else
		{
			posY -= sizeY;			// advance the Y position - newline (TODO: MagNum)
			posY -= 7;
			posX = 0;			// make the following character at the very left
		}
	}
}