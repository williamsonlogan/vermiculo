// Includes
#include "template.h"

// Namespace
using namespace AGK;

app App;

int screenWidth = 256;
int screenHeight = 144;

float playerX = 8.0f;
float playerY = 8.0f;
float playerA = 0.0f;

int mapHeight = 16;
int mapWidth = 16;

float FOV = 3.14159f / 4.0f;
float fogDepth = 16;

std::string map;

void app::Begin(void)
{
	agk::SetVirtualResolution (screenWidth, screenHeight);
	agk::SetClearColor( 0,0,0 ); // black
	agk::SetSyncRate(60,0);
	agk::SetFolder("media");
	agk::SetDefaultMagFilter(0);
	
	
	//buffer = PixelBuffer(screenWidth, screenHeight);
	
	map += "################";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..........#...#";
	map += "#..........#...#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#..............#";
	map += "#......#########";
	map += "#..............#";
	map += "#..............#";
	map += "################";
	
}

int app::Loop (void)
{
	agk::Print((int)std::ceil(agk::ScreenFPS()));
	
	//move forward
	if (agk::GetRawKeyState(87))
	{
		playerX += cosf(playerA) * 3.0f * agk::GetFrameTime();
		playerY += sinf(playerA) * 3.0f * agk::GetFrameTime();
	}
	
	//move backwards
	if (agk::GetRawKeyState(83))
	{
		playerX -= cosf(playerA) * 3.0f * agk::GetFrameTime();
		playerY -= sinf(playerA) * 3.0f * agk::GetFrameTime();
	}
	
	//rotate to the right
	if (agk::GetRawKeyState(68))
	{
		playerA += (0.8f) * agk::GetFrameTime();
	}
	
	//rotate to the left
	if (agk::GetRawKeyState(65))
	{
		playerA -= (0.8f) * agk::GetFrameTime();
	}
	
	PixelBuffer buffer(screenWidth, screenHeight);
	
	for (int x = 0; x < screenWidth; x++)
	{
		// For each column, calculate the projected ray angle into world space
		float rayAngle = (playerA - FOV / 2.0f) + ((float)x / (float)screenWidth) * FOV;
		
		float distanceToWall = 0.0f;
		bool hitWall = false;
		
		float eyeX = cosf(rayAngle);
		float eyeY = sinf(rayAngle);
		
		while (!hitWall && distanceToWall < fogDepth)
		{
			distanceToWall += 0.1f;
			
			int testX = (int)(playerX + eyeX * distanceToWall);
			int testY = (int)(playerY + eyeY * distanceToWall);
			
			// Test if ray is out of bounds
			if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight)
			{
				hitWall = true;
				distanceToWall = fogDepth;
			}
			else
			{
				// ray is inbounds so test if its a wall
				if (map[testX * mapWidth + testY] == '#')
				{
					hitWall = true;
					//distanceToWall = testX * cosf(playerA) - testY * sinf(playerA);
				}
			}
		}
		
		// calculate floor and ceiling distance
		int ceiling = (float)(screenHeight / 2.0f) - screenHeight / ((float)distanceToWall);
		int floor = screenHeight - ceiling;
		
		int wallShade = 255;
		
		if (distanceToWall <= fogDepth / 4.0f)		wallShade = 223;
		else if (distanceToWall < fogDepth / 3.0f)	wallShade = 191;
		else if (distanceToWall < fogDepth / 2.0f)	wallShade = 159;
		else if (distanceToWall < fogDepth)			wallShade = 127;
		else										wallShade = 0;
		
		for(int y = 0; y < screenHeight; y++)
		{
			if(y <= ceiling)
				buffer.Poke(x, y, 0, 0, 0);
			else if (y > ceiling && y <= floor)
				buffer.Poke(x,y, 0, 0, wallShade);
			else
			{
				int floorShade = 0;
				
				float b = 1.0f - (((float)y - screenHeight / 2.0f) / ((float)screenHeight / 2.0f));
				if (b < 0.25)		floorShade = 255;
				else if (b < 0.5)	floorShade = 191;
				else if (b < 0.75)	floorShade = 127;
				else if (b < 0.9)	floorShade = 63;
				else				floorShade = 0;
				
				buffer.Poke(x, y, 0, floorShade, 0);
			}
		}
	}
	
	for(int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			buffer.Poke(x, y, 0, 0, 0);
	
	buffer.Poke(1, 1, 255, 0, 0);
	
	buffer.Draw();
	
	agk::Sync();
	
	return 0; // return 1 to close app
}


void app::End (void)
{
	
}
