#ifndef TEXTRENDERER_H_
#define TEXTRENDERER_H_

#include "bidimensionalrenderer.h"

class TextRenderer
{
private:
	int idTexUnicode00;
	BidimensionalRenderer * bidRenderer;
public:
	TextRenderer();
	void init(BidimensionalRenderer * pBidRenderer);
	void render(const char * text) const;
};

#endif