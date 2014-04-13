#ifndef MAZEMAP_H
#define MAZEMAP_H

/*
 * Contains the robot's representation of the maze in memory.
 * Arrays of wall states determine whether or not the robot
 * can travel.
 */

#include "define.h"

// holds the state of the wall
typedef enum {
	WALL = 1,
	NOWALL = 0,
	UNKNOWN = -1
} WallState;

typedef struct {
	WallState horizWalls[MAZE_HEIGHT - 1][MAZE_WIDTH];
	WallState vertWalls[MAZE_HEIGHT][MAZE_WIDTH - 1];

} MazeMap;

// constructor
MazeMap mazemap_create();

//
// main methods
//

BOOL mazemap_is_wall(MazeMap* mazeMap, int x, int y, Direction direction);
BOOL mazemap_is_wall_r(MazeMap* mazeMap, int x, int y, Direction direction, Rotation rotation);
void mazemap_set_wall(MazeMap* mazeMap, BOOL state, int x, int y, Direction direction);

BOOL mazemap_get_look_position(int x, int y, Direction direction, int* xLook, int* yLook);
void mazemap_one_ahead_direction(Direction direction, int* x, int* y);

//
// helper methods
//

Direction rotation_to_direction(Direction curDirection, Rotation rotation);
Rotation direction_to_rotation(Direction curDirection, Direction targetDirection);

#endif
