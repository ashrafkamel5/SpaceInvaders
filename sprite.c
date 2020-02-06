/**
 * sprite implementation of Space Invaders game
 *
 * Copyright 2018 by Ashraf Kamel
 * You may use, edit, run or distribute this file
 * as long as the above copyright notice remains.
 */
#include "sprite.h"
#include "Nokia5110.h"
#include <stdint.h>
#include "..//tm4c123gh6pm.h"
#include "ADC.h"
#include "Images.h"

#define MAX_ENEMY_COLUMNS 4
#define MAX_ENEMY_ROWS 3
#define NUM_BONUS_ENEMY 1
#define NUM_PLAYERS 1
#define MAX_ENEMIES (MAX_ENEMY_COLUMNS * MAX_ENEMY_ROWS + NUM_BONUS_ENEMY) // 5 enemies in one row * 3 rows + bonus enemy
#define MAX_BUNKERS 3
#define MAX_SHOTS (MAX_ENEMIES + NUM_PLAYERS)
#define SHOTDELAY 30
#define ENEMYDELAY 30


sprite player = {32 ,47 ,{PlayerShip0 , BigExplosion0 , BigExplosion1},false ,false ,0 , 1};

sprite enemy[MAX_ENEMIES];
sprite bunker[3];
Sshot shot[MAX_SHOTS];
Sshot specialShot[2];

int level = 0 ,ENEMY_NUM ,BUNKER_NUM , SHOT_NUM ,SHOT_Count,SPECIAL_Count ,fNUM = 0, Semaphore = 0;
unsigned short shotspeed = 0;
void Draw()
{
	int i;
	fNUM++;
	Nokia5110_ClearBuffer();
	//Nokia5110_DisplayBuffer();      // draw buffer
	//draw player
	Nokia5110_PrintBMP(player.x, player.y, player.image[0], 0); // player ship middle bottom
  //draw bunker
	for(i = 0 ; i < BUNKER_NUM ; i++)
	{
		if (bunker[i].life > 7)
			Nokia5110_PrintBMP(bunker[i].x,bunker[i].y , bunker[i].image[0], 0);
		else if (bunker[i].life > 4)
			Nokia5110_PrintBMP(bunker[i].x,bunker[i].y , bunker[i].image[1], 0);
		else if (bunker[i].life > 0)
			Nokia5110_PrintBMP(bunker[i].x,bunker[i].y , bunker[i].image[2], 0);
	}
	//draw enemies
	for(i = 0; i < ENEMY_NUM; i++)
	{
		if(enemy[i].life > 0)
		{
		   if(fNUM < 15)
			 {
			     Nokia5110_PrintBMP(enemy[i].x, enemy[i].y, enemy[i].image[0], 0);
			 }
			 else
			 {
				   Nokia5110_PrintBMP(enemy[i].x, enemy[i].y, enemy[i].image[1], 0);
					 if(fNUM == 30)
						 fNUM = 0;
			 }
		}
		else if(enemy[i].life == 0)
		{
			 Nokia5110_PrintBMP(enemy[i].x, enemy[i].y, enemy[i].image[2], 0);
			 player.score += enemy[i].score;
			 enemy[i].delay --;
			 if(enemy[i].delay == 0)
			 {
				 enemy[i].delay = ENEMYDELAY;
				 enemy[i].life--;
			 }
    }
	}
	//draw shots
	for(i = 0; i < SHOT_NUM; i++)
	{
		if(shot[i].life > 0)
		{
		   Nokia5110_PrintBMP(shot[i].x, shot[i].y, shot[i].image, 0);
		}
		else if(shot[i].life == 0)
		{
			 Nokia5110_PrintBMP(shot[i].x, shot[i].y, SmallExplosion0, 0);
			 shot[i].delay--;
			 if(shot[i].delay == 0)
			 { 
				 shot[i].life--;
				 shot[i].delay = SHOTDELAY;
			 }
		}
	}
	
  Nokia5110_DisplayBuffer();     // draw buffer
}


void init_Bunker(int level)
{
	int i;
	if(level < 5)
	{
	    BUNKER_NUM = 1;
			bunker[i].x = 32;
			bunker[i].y = 47 - PLAYERH;
			bunker[i].fire = false;
			bunker[i].life = 10;
			bunker[i].score = 0;
			bunker[i].image[0] = Bunker0;
		  bunker[i].image[1] = Bunker1;
      bunker[i].image[2] = Bunker2;
	}
}


void init_enemies(int level)
{
	int i;
	switch(level)
		case 0 :
			ENEMY_NUM = 5;
			for(i = 0; i < ENEMY_NUM;i++)
			{
				enemy[i].x = i * 16;
				enemy[i].y = ENEMY10H;
				enemy[i].fire = false;
				enemy[i].delay = 20;
				if(i == 0)
				{						
    		 enemy[i].life = 1;
				 enemy[i].score = 10;
			   enemy[i].image[0] = SmallEnemy10PointA;
		     enemy[i].image[1] = SmallEnemy10PointB;
			   enemy[i].image[2] = SmallExplosion0;
			  }
				else if(i == 1) 
				{
					 enemy[i].life = 2;
					 enemy[i].score = 20;
					 enemy[i].image[0] = SmallEnemy20PointA;
			     enemy[i].image[1] = SmallEnemy20PointB;
				   enemy[i].image[2] = SmallExplosion0;
				}
				else if(i == 2)
				{	  
				   enemy[i].life = 2;
				   enemy[i].score = 20;
				   enemy[i].image[0] = SmallEnemy20PointA;
			     enemy[i].image[1] = SmallEnemy20PointB;
				   enemy[i].image[2] = SmallExplosion0;
				}
				else if(i == 3)
				{	 
					 enemy[i].life = 3;
					 enemy[i].score = 30;
					 enemy[i].image[0] = SmallEnemy30PointA;
			     enemy[i].image[1] = SmallEnemy30PointB;
				   enemy[i].image[2] = SmallExplosion0;
				}
				else if(i == 4)
				{
					 enemy[i].life = 3;
					 enemy[i].score = 30;
					 enemy[i].image[0] = SmallEnemy30PointA;
			     enemy[i].image[1] = SmallEnemy30PointB;
				   enemy[i].image[2] = SmallExplosion0;
				}					
				
			}
			
}

void init_Shots(void)
{
	int i;
  SHOT_NUM = 6;
	SHOT_Count = 0;
  for(i = 0; i < SHOT_NUM;i++)
  {
  	shot[i].life = -1;
  	shot[i].image = Laser0;	
		shot[i].delay = SHOTDELAY;
	}
}

void initGame()
{
	Semaphore = 0;
	init_enemies(0);
  init_Bunker(0);	
	init_Shots();
}
void detectCollision(sprite* obj0,Sshot* obj1)
{
		boundary A ,B;
		A.top = obj0->y - obj0->image[0][22];
	  A.bottom = obj0->y;
	  A.left = obj0->x;
	  A.right = obj0->x + obj0->image[0][18];
	  
   	B.top = obj1->y - obj1->image[22];
	  B.bottom = obj1->y;
	  B.left = obj1->x;
	  B.right = obj1->x + obj1->image[18];
	
	  if(A.right > B.left && A.left < B.right && A.top < B.bottom && A.bottom > B.top)
		{
			obj0->life--;
			obj1->life--;
			SHOT_Count--;
		}
}

void detectShotCollision(Sshot* obj0,Sshot* obj1)
{
		boundary A ,B;
		A.top = obj0->y - obj0->image[22];
	  A.bottom = obj0->y;
	  A.left = obj0->x;
	  A.right = obj0->x + obj0->image[18];
	  
   	B.top = obj1->y - obj1->image[22];
	  B.bottom = obj1->y;
	  B.left = obj1->x;
	  B.right = obj1->x + obj1->image[18];
	  if(A.right > B.left && A.left < B.right && A.top < B.bottom && A.bottom > B.top)
		{
			obj0->life --;
			obj1->life --;
			SHOT_Count -= 2;
		}
}
void detectCollisions()
{
		int i,j;
		for(i = 0; i < ENEMY_NUM ; i++)
	  {
			if(enemy[i].life > 0)
			{	
			  for(j = 0;j < SHOT_NUM ; j++)
			  { 
					if(shot[j].life > 0)
			  		detectCollision(&enemy[i],&shot[j]);
				}
			}
	  }
//		for(i = 0; i < SHOT_NUM ; i++)
//	  {
//			if(shot[i].life > 0)
//			{	
//			  for(j = 0;j < SHOT_NUM ; j++)
//			  { 
//					if(shot[j].life > 0)
//			  		detectShotCollision(&shot[i],&shot[j]);
//				}
//			}
//	  }
		for(i = 0; i < BUNKER_NUM ; i++)
	  {
			if(bunker[i].life > 0)
			{
			  for(j = 0;j < SHOT_NUM ; j++)
			  {
					if(shot[j].life > 0)
			  		detectCollision(&bunker[i],&shot[j]);
				}
			}
	  }
}
void update_enemies(void)
{
	int i;
	for(i = 0; i < ENEMY_NUM ;i++)
	{
		if((enemy[i].x + enemy[i].image[0][18]) >= 83)
		{
			enemy[i].x = 0;
			enemy[i].y += enemy[i].image[0][22];
		}
		else
		enemy[i].x++;
	}
}

void update()
{
	int i;
	shotspeed++;
	if(player.fire == true)
	{
		if(SHOT_Count < SHOT_NUM )
		{
	      shot[SHOT_Count].life = 1;
	      shot[SHOT_Count].x = player.x + (PLAYERW / 2);
	      shot[SHOT_Count].y = player.y - PLAYERH;
	      shot[SHOT_Count].image = Missile0;
	      SHOT_Count++;
		}
		player.fire = false;
	}
	if(player.special_fire == true)
	{
		if(SHOT_Count < SHOT_NUM )
		{
	      specialShot[SPECIAL_Count].life = 1;
	      specialShot[SPECIAL_Count].x = player.x + (PLAYERW / 2);
	      specialShot[SPECIAL_Count].y = player.y - PLAYERH;
	      specialShot[SPECIAL_Count].image = Laser0;
	      SPECIAL_Count++;
		}
		player.special_fire = false;
	}

   	for(i = 0; i < SHOT_NUM ; i++)
	  {
	   		if(shot[i].life > 0)
	   		{
          if(shot[i].y == shot[i].image[22])	
					{
						shot[i].life = 0;
						SHOT_Count--;
					}
					else
					{
	   		    shot[i].y--;
					}
	   		}
	   }
	update_enemies();
	detectCollisions();
}
