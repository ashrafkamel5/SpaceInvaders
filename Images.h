#ifndef __IMAGES_H__
#define __IMAGES_H__ 1

// *************************** Capture image dimensions out of BMP**********
#define BUNKERW     ((unsigned char)Bunker0[18])
#define BUNKERH     ((unsigned char)Bunker0[22])
#define ENEMY30W    ((unsigned char)SmallEnemy30PointA[18])
#define ENEMY30H    ((unsigned char)SmallEnemy30PointA[22])
#define ENEMY20W    ((unsigned char)SmallEnemy20PointA[18])
#define ENEMY20H    ((unsigned char)SmallEnemy20PointA[22])
#define ENEMY10W    ((unsigned char)SmallEnemy10PointA[18])
#define ENEMY10H    ((unsigned char)SmallEnemy10PointA[22])
#define ENEMYBONUSW ((unsigned char)SmallEnemyBonus0[18])
#define ENEMYBONUSH ((unsigned char)SmallEnemyBonus0[22])
#define LASERW      ((unsigned char)Laser0[18])
#define LASERH      ((unsigned char)Laser0[22])
#define MISSILEW    ((unsigned char)Missile0[18])
#define MISSILEH    ((unsigned char)Missile0[22])
#define PLAYERW     ((unsigned char)PlayerShip0[18])
#define PLAYERH     ((unsigned char)PlayerShip0[22])

//****************************BitmabImages***********************

// icon showing the number of lifes the player has (small player ship icon)
extern const unsigned char Life[];

// *************************** Images ***************************
// enemy ship that starts at the top of the screen (arms/mouth closed)
// width=16 x height=10
extern const unsigned char SmallEnemy30PointA[];

// enemy ship that starts at the top of the screen (arms/mouth open)
// width=16 x height=10
extern const unsigned char SmallEnemy30PointB[];

// enemy ship that starts in the middle of the screen (arms together)
// width=16 x height=10
extern const unsigned char SmallEnemy20PointA[];

// enemy ship that starts in the middle of the screen (arms apart)
// width=16 x height=10
extern const unsigned char SmallEnemy20PointB[];

// enemy ship that starts at the bottom of the screen (arms down)
// width=16 x height=10
extern const unsigned char SmallEnemy10PointA[];

// enemy ship that starts at the bottom of the screen (arms up)
// width=16 x height=10
extern const unsigned char SmallEnemy10PointB[];

// image of the player's ship
// includes two blacked out columns on the left and right sides of the image to prevent smearing when moved 2 pixels to the left or right
// width=18 x height=8
extern const unsigned char PlayerShip0[];

// small, fast bonus enemy that occasionally speeds across the top of the screen after enough enemies have been killed to make room for it
// includes two blacked out columns on the left and right sides of the image to prevent smearing when moved 2 pixels to the left or right
// width=20 x height=7
extern const unsigned char SmallEnemyBonus0[];

// small shield floating in space to cover the player's ship from enemy fire (undamaged)
// width=18 x height=5
extern const unsigned char Bunker0[];

// small shield floating in space to cover the player's ship from enemy fire (moderate generic damage)
// width=18 x height=5
extern const unsigned char Bunker1[];

// small shield floating in space to cover the player's ship from enemy fire (heavy generic damage)
// width=18 x height=5
extern const unsigned char Bunker2[];

// large explosion that can be used upon the demise of the player's ship (first frame)
// width=18 x height=8
extern const unsigned char BigExplosion0[];

// large explosion that can be used upon the demise of the player's ship (second frame)
// width=18 x height=8
extern const unsigned char BigExplosion1[];

// small explosion best used for the demise of an enemy
// width=16 x height=10
extern const unsigned char SmallExplosion0[];

// a missile in flight
// includes one blacked out row on the top, bottom, and right of the image to prevent smearing when moved 1 pixel down, up, or left
// width=4 x height=9
extern const unsigned char Missile0[];

// a missile in flight
// includes one blacked out row on the top, bottom, and left of the image to prevent smearing when moved 1 pixel down, up, or right
// width=4 x height=9
extern const unsigned char Missile1[];

// a laser burst in flight
// includes one blacked out row on the top and bottom of the image to prevent smearing when moved 1 pixel up or down
// width=2 x height=9
extern const unsigned char Laser0[];

extern const unsigned char LaserExplosion[];

// full title screen 504 bytes Nokia format. Should be copied into Screen buffer
extern const unsigned char title[];
#endif
