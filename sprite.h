
#include <stdbool.h>
#ifndef __sprite_h__
#define __sprite_h__ 1

typedef struct sprite
{
	int x;
	int y;
	const unsigned char* image[3];
	bool fire;
	bool special_fire;
	int life;
	int delay;
	int score;
} sprite;

typedef struct boundary
{
	unsigned char top;
	unsigned char bottom;
	unsigned char left;
	unsigned char right;
} boundary;

typedef struct shot
{
	int x;
	int y;
	const unsigned char* image;
	int life;
	int delay;
} Sshot;
extern sprite player;

extern int fNUM;
extern int Semaphore;


void Draw(void);
void initGame(void);
void detectCollisions(void);
void update(void);
#endif

