#ifndef TEXTURE_H
#define TEXTURE_H
#include "../../Dependencies/stb_image.h"
#include <string>
namespace Drawables
{
	class Texture
	{
	public:
		Texture(const std::string& fileName = "");
		~Texture();

		const bool operator==(const Texture& other) const;
		const bool isLoaded() const;

		void init();
		void setActive();

		const int getWidth() const;
		const int getHeight() const;

	private:
		unsigned int _texID;
		std::string _filePath;
		unsigned char* _pixels;
		bool _loaded;
		int _width;
		int _height;
		int _bitsPerPixel;
	};
}

#endif // !TEXTURE_H
