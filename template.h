#ifndef _H_APP
#define _H_APP

// Link to AGK files
// _WIN32 = we're in windows
#ifdef _WIN32
#include "AGK.h"
#else
#include "agk.h"
#endif

// libraries
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

// other includes
#include "graphics.h"

// used in Core.mm to set the window properties
#define DEVICE_WIDTH 1280
#define DEVICE_HEIGHT 720
#define WINDOW_TITLE "Vermiculo"
#define FULLSCREEN 0

// used to make a more unique folder for the write path
#define COMPANY_NAME "Feesh Games"

// Global values for the app
class app
{
	public:

		// global game vars

	public:

		// constructor
		app() {}
        ~app() {}

		// main app functions - mike to experiment with a derived class for this..
        void Begin( void );
        int Loop( void );
        void End( void );
	
	//PixelBuffer buffer;
};

extern app App;

#endif
