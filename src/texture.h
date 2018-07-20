#ifndef TEXTURE_H_
#define TEXTURE_H_

class Texture
{
private:
	unsigned int tex;
public:
	Texture();
	void load(const char * path);
	void bind() const;
	void clear();
};

#endif