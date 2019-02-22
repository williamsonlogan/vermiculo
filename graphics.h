#pragma once

// Link to AGK files
// _WIN32 = we're in windows
#ifdef _WIN32
#include "AGK.h"
#else
#include "agk.h"
#endif

class PixelBuffer
{
public:
    PixelBuffer();
	PixelBuffer(int width, int height);
    
	~PixelBuffer();
    
    //TODO: GetPixel(x, y)
    
    int getID() const { return _id; }
    int getImage() const { return _image; }
    int getSprite() const { return _sprite; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    
	void Draw();
    
	void Clear();
    
	void Poke(int x, int y, int r, int g, int b);
    
	void Poke(int x, int y, int r, int g, int b, int a);
    
	void Poke(int x, int y, int color);
    
private:
    int _id;
    int _image;
    int _sprite;
    int _width;
    int _height;
};
